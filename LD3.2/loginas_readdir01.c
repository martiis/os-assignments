/* Vardenis Pavardenis KTK varpav */
/* Failas: loginas_readdir01.c */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int openDirectory();

int openDirectory()
{
    char *cwd;
    struct dirent *dp;
    cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
    DIR *dir;
    dir = opendir(cwd);

    do {
        if((dp = readdir(dir)) != NULL) {
            //KAIP d_ino atspausdinti?!?
            //puts(dp->d_ino);
            printf("%s\n", dp->d_name);
        }
    } while(dp != NULL);

    closedir(dir);
}

int main()
{
    openDirectory();
    return 0;
}