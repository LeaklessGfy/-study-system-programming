#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int r;
  struct stat sb;
  char filename[255];

  if (argc < 2) {
    fprintf(stderr, "Usage: exo2 <pathname>\n");
    exit(EXIT_FAILURE);
  }

  if (lstat(argv[1], &sb) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }

  printf("Numéro d'inœud : %ld\n", (long)sb.st_ino);
  printf("Taille du fichier : %lld octets\n", (long long)sb.st_size);
  printf("Dernière modification : %s", ctime(&sb.st_mtime));
  printf("Type de fichier : ");

  switch (sb.st_mode & S_IFMT) {
  case S_IFDIR:
    printf("d\n");
    break;
  case S_IFREG:
    printf("f\n");
    break;
  case S_IFLNK:
    printf("l\n");
    r = readlink(argv[1], &filename, sb.st_size + 1);
    filename[r] = '\0';
    printf("« %s » pointe vers « %s »\n", argv[1], filename);
    break;
  default:
    printf("?\n");
    break;
  }

  exit(EXIT_SUCCESS);
}
