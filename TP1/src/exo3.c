#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void get_lstat(char *pathname, struct stat *sb)
{
    if (lstat(pathname, sb) == -1)
    {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
}

void print_symbolic(char *path, struct stat sb)
{
    int r;
    char filename[255];

    r = readlink(path, &filename, sb.st_size + 1);

    if (r == -1)
    {
       perror("readlink");
       exit(EXIT_FAILURE);
    }

    if (r > sb.st_size)
    {
       fprintf(stderr, "la taille du lien symbolique a augmenté"
                       "entre lstat() et readlink()\n");
       exit(EXIT_FAILURE);
    }

    filename[r] = '\0';
    printf("« %s » pointe vers « %s »\n", path, filename);
}

void print_file(char *path, struct stat sb)
{
    printf("Numéro d'inœud :                   %ld\n", (long) sb.st_ino);
    printf("Taille du fichier :                %lld octets\n", (long long) sb.st_size);
    printf("Dernière modification :            %s", ctime(&sb.st_mtime));
    printf("Type de fichier :                  ");
    
    switch (sb.st_mode & S_IFMT)
    {
        case S_IFREG:
            printf("f\n");
            break;
        case S_IFLNK:
            printf("l\n");
            print_symbolic(path, sb);
            break;
        default:
            printf("?\n");
            break;
    }
}

void print_dir(char *path, struct stat sb)
{
    DIR *dirp;
    struct dirent *dirt;
    struct stat sbc;
    char fullname[255];

    dirp = opendir(path);
    
    while (dirt = readdir(dirp))
    {
        //strncat(pathname, dirt->d_name, 2);
        printf("- %s\n", fullname);
        get_lstat(fullname, &sbc);
        print_file(fullname, sbc);
    }
    
    closedir(dirp);
}

int main(int argc, char *argv[])
{
    int i;
    struct stat sb;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: exo3 <pathname>\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; i++)
    {
        get_lstat(argv[i], &sb);
    
        if (S_ISDIR(sb.st_mode))
            print_dir(argv[i], sb);
        else
            print_file(argv[i], sb);
    }

    exit(EXIT_SUCCESS);
}
