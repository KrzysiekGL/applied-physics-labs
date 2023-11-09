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

const char * filename = "file.txt";
const char * pathname = "/proc/self/fd";
const char * slash = "/";

int main(int argc, char ** argv, char ** envp)
{
  int fd = open(filename, O_CREAT, O_RDWR);

  // read paths of all fds in the /proc/self/fd
  DIR * dirp = opendir(pathname);
  if (dirp == NULL) {
    perror("opendir");
    exit(EXIT_FAILURE);
  }

  char * retrieved_path = malloc(PATH_MAX);
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

    char * buf = malloc(bufsiz);
    if (buf == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

    // retrieve the path fro mthe symblic link and store it in the 'buf'
    nbytes = readlink(retrieved_path, buf, bufsiz);
    if (nbytes == -1) {
      perror("readlink");
      exit(EXIT_FAILURE);
    }

    printf("%s -> %.*s\n", retrieved_path, (int) nbytes, buf);

    memset(retrieved_path, 0, strlen(retrieved_path));
    free(buf);
  }

  free(retrieved_path);
  closedir(dirp);
  close(fd);
  return 0;
}
