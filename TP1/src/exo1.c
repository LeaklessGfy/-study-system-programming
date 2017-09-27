#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct stat sb;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: exo1 <pathname>\n");
        exit(EXIT_FAILURE);
    }

    if (stat(argv[1], &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("Numéro d'inœud :                   %ld\n", (long) sb.st_ino);
    printf("Taille du fichier :                %lld octets\n", (long long) sb.st_size);
    printf("Dernière modification :            %s", ctime(&sb.st_mtime));
    printf("Type de fichier :                  ");

    switch (sb.st_mode & S_IFMT)
    {
        case S_IFDIR:
            printf("d\n");
            break;
        case S_IFREG:
            printf("f\n");
            break;
        default:
            printf("?\n");
            break;
    }

    exit(EXIT_SUCCESS);
}
