#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define handle_error(msg) \
  do { perror((msg)); exit(EXIT_FAILURE); } while(0)

void search_with_fopen(const char * file_name, const char * pattern) {
  FILE * f = fopen(file_name, "r");
  char s[256];
  while (fgets(s, sizeof s, f)) {
    char * occurence;
    if (strstr(s, pattern)) {
      printf("occurence: %s\n", s);
      break;
    }
  }
  fclose(f);
}

void search_with_mmap(const char * file_name, const char * pattern) {
  int fd = open(file_name, O_RDONLY);
  if (fd == -1)
    handle_error("open");

  // get the file's size
  struct stat sb;
  if (fstat(fd, &sb) == -1)
    handle_error("fstat");

  char * addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED)
    handle_error("mmap");

  char * pos;
  if ((pos = strstr(addr, pattern))) {
    printf("occurence found at position %td\n", pos - addr);
  }

  munmap(addr, sb.st_size);
  close(fd);
}

int main(int argc, char ** argv, char ** env)
{
  const char * file_name = argc > 1 ? argv[1] : "big_text.txt";
  const char * pattern = argc > 2 ? argv[2] : "Jesus";

  clock_t start = clock();
  search_with_fopen(file_name, pattern);
  clock_t end = clock();
  float time = (float)(end-start)/CLOCKS_PER_SEC;
  printf("search of pattern %s in the file opend with fopen took %f seconds\n", pattern, time);

  start = clock();
  search_with_mmap(file_name, pattern);
  end = clock();
  time = (float)(end-start)/CLOCKS_PER_SEC;
  printf("search of pattern %s in the file opend with mmap took %f seconds\n", pattern, time);

  return 0;
}
