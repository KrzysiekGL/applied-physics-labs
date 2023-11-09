#include <cstdlib>
#include <fcntl.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>

#include <thread>
#include <iostream>

int is_already_open(const char * filename)
{
  const char * pathname = "/proc/self/fd";
  const char * slash = "/";

  // read paths of all fds in the /proc/self/fd
  DIR * dirp = opendir(pathname);
  if (dirp == NULL) {
    perror("opendir");
    exit(EXIT_FAILURE);
  }

  char * retrieved_path = (char *)malloc(PATH_MAX);
  ssize_t nbytes;
  ssize_t bufsiz = 256;
  struct stat sb;
  struct dirent * entry;

  while ((entry = readdir(dirp)) != NULL) {
    // if not a symbolic link, skip the entry
    if (entry->d_type != DT_LNK)
      continue;

    // combine the pathname of the entry
    strncpy(retrieved_path, pathname, strlen(pathname));
    strncat(retrieved_path, slash, strlen(slash));
    strncat(retrieved_path, entry->d_name, strlen(entry->d_name));

    char * buf = (char*)malloc(bufsiz);
    if (buf == NULL) {
      perror("malloc");
      return -1;
    }

    // retrieve the path fro mthe symblic link and store it in the 'buf'
    nbytes = readlink(retrieved_path, buf, bufsiz);
    if (nbytes == -1) {
      perror("readlink");
      return -1;
    }

    char * fd_buf = (char*)malloc(nbytes);
    strncpy(fd_buf, buf, nbytes);

    if (strncmp(filename, fd_buf, nbytes) == 0)
      return 1;

    memset(retrieved_path, 0, strlen(retrieved_path));
    free(fd_buf);
    free(buf);
  }

  free(retrieved_path);
  closedir(dirp);
  return 0;
}

void access_file(const char * filename,
		 const char * text_to_write,
		 const int flags,
		 const mode_t mode)
{
  // try to open a file and write something to it 10 times
  for (int i=0; i<10; ++i) {
    if (is_already_open(filename) != 0)
      continue;

    int fd;
    if((fd = open(filename, flags, mode)) ==  -1) {
      perror("open");
      return;
    }

    if((write(fd, text_to_write, sizeof text_to_write) == -1)) {
      perror("write");
      close(fd);
      return;
    }

    close(fd);
  }
}

int main(int argc, char ** argv, char ** envp)
{
  if (argc != 2 && argc != 3) {
    fprintf(stderr, "Usage: %s <pathname> [0|1]\n", argv[0]);
    exit(EXIT_FAILURE);
  }


  const char * filename = argv[1];
  int flags = O_CREAT;
  mode_t mode = O_RDWR;

  std::string A, B;
  const unsigned int what_text_blob = argv[2] ? std::atoi(argv[2]) : 0;
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
