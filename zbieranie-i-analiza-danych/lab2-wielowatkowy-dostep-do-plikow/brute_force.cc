#include <cstdio>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <string>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void access_file(const char * filename,
		 const char * text_to_write,
		 const int flags,
		 const mode_t mode)
{
  int fd;
  if((fd = open(filename, flags, mode)) ==  -1) {
    int errsv = errno;
    printf("%s: open() failed with errno %d\n", text_to_write,  errsv);
    return;
  }

  for(int i = 0; i<10; ++i) {
    if((write(fd, text_to_write, sizeof text_to_write) == -1)) {
      int errsv = errno;
      printf("%s: write() failed with errno %d\n", text_to_write, errno);
    }
  }

  close(fd);
}

int main(int argc, char ** argv, char ** envp)
{
  int flags;
  mode_t mode;

  const char * filename = argv[1] ? argv[1] : "file.txt";
  const unsigned int which_mode = argv[2] ? std::atoi(argv[2]) : 0;
  switch (which_mode) {
  case 0:
    flags = O_RDWR;
    mode = O_SYNC;
    break;
  case 1:
    flags = O_RDWR;
    mode = O_APPEND;
    break;
  }

  std::string A, B;
  const unsigned int what_text_blob = argv[3] ? std::atoi(argv[3]) : 0;
  switch (what_text_blob) {
  case 0:
    A = std::string("A");
    B = std::string("B");
    break;
  case 1:
    A = std::string("Ala ma kota\n");
    B = std::string("Bob nie ma psa\n");
  }

  std::thread t1(access_file, filename, A.c_str(), flags , mode);
  std::thread t2(access_file, filename, B.c_str(), flags , mode);
  t1.join();
  t2.join();

  return 0;
}
