#include <thread>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const char * default_pathname = "/tmp/task-fifo";
const unsigned int default_sleep_period = 1;

typedef struct {
  float vals[16];
  float * read_ptr;
  float * write_ptr;
} cyclic_buffer;

cyclic_buffer buffer;

void write_element(cyclic_buffer * buf, float val) {
  if (buf->write_ptr >= buf->vals+16)
    buf->write_ptr = buf->vals;
  *(buf->write_ptr) = val;
  if (buf->write_ptr == buf->read_ptr)
    buf->read_ptr++;
  buf->write_ptr++;
}

float read_element(cyclic_buffer * buf) {
  if (buf->read_ptr >= buf->vals+16)
    buf->read_ptr = buf->vals;
  float ret = *(buf->read_ptr);
  buf->read_ptr++;
  return ret;
}

void receive_data(const char * pathname, const unsigned int sleep_period)
{
  char buf[64];
  while (1) {
    int fd = open(pathname, O_RDONLY);
    if (fd == -1) {
      perror("open");
      exit(EXIT_FAILURE);
    }

    memset(buf, 0, sizeof buf);
    read(fd, buf, 8);
    //printf("Received: %s\n", buf);
    close(fd);

    float val = atof(buf);
    //printf("Received: %f\n", val);
    write_element(&buffer, val);

    sleep(sleep_period);
  }
}

int main(int argc, char ** argv, char ** env)
{
  const unsigned int sleep_period = argv[1] ? atoi(argv[1]) : default_sleep_period;
  const char * pathname = argv[2] ? argv[2] : default_pathname;

  if (!mkfifo(pathname, 0666)) {
    perror("mkfifo");
    exit(EXIT_FAILURE);
  }

  // initialize the buffer
  for (int i = 0; i<16; ++i)
    buffer.vals[i] = 0;
  buffer.write_ptr = buffer.vals;
  buffer.read_ptr = buffer.vals;

  // run the receiver
  std::thread receiver(receive_data, pathname, sleep_period);

  // print buffer contents
  printf("Press enter to continue...\n");
  while (getchar()) {
    for (int i=0; i<16; ++i)
      printf("%f, ", read_element(&buffer));
    printf("\nPress enter to continue...\n");
  }

  // wait for the receiver to finish (hint: never)
  receiver.join();

  return 0;
}
