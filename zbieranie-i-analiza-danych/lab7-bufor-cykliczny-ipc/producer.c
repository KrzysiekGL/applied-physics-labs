#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>

const char * default_pathname = "/tmp/task-fifo";
const unsigned int default_sleep_period = 2;

int main(int argc, char ** argv, char ** evn)
{
  const unsigned int sleep_period = argv[1] ? atoi(argv[1]) : default_sleep_period;
  const char * pathname = argv[2] ? argv[2] : default_pathname;

  if (!mkfifo(pathname, 0666)) {
    perror("mkfifo");
    exit(EXIT_FAILURE);
  }

  char buf[64];
  while(1) {
    int fd = open(pathname, O_WRONLY);
    if (fd == -1) {
      perror("open");
      exit(EXIT_FAILURE);
    }

    float val = sin((float) ((int)time(NULL)%10));
    snprintf(buf, sizeof buf, "%f", val);
    printf("Insert %s\n", buf);
    write(fd, buf, strlen(buf)+1);
    close(fd);
    memset(buf, 0, sizeof buf);
    sleep(sleep_period);
  }

  return 0;
}
