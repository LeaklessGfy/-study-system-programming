#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void get_stat(char *pathname, struct stat *sb) {
  if (stat(pathname, sb) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
  time_t t;
  struct stat sb;

  if (argc < 2) {
    fprintf(stderr, "Usage: exo4 <pathname>\n");
    exit(EXIT_FAILURE);
  }

  get_stat(argv[1], &sb);
  t = sb.st_mtime;

  while (1) {
    get_stat(argv[1], &sb);
    if (t != sb.st_mtime) {
      printf("Change occurd on file %s\n", argv[1]);
      exit(EXIT_SUCCESS);
    }
    usleep(1000);
  }

  exit(EXIT_SUCCESS);
}
