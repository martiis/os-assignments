/* Vardenis Pavardenis KTK varpav */
/* Failas: loginas_stat01.c */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>

int getStat();

int getStat(char * fdir)
{
    char *cwd;
    struct dirent *dp;
    struct stat    statbuf;
    struct passwd  *pwd;
    struct group   *grp;
    DIR *dir;

    cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
    dir = opendir(cwd);

    do {
        if((dp = readdir(dir)) != NULL) {
            if(strcmp(dp->d_name, fdir) != 0) {
                continue;
            }

            printf("Found %s\n\n", dp->d_name);
            stat(dp->d_name, &statbuf);

            printf("i-node \t\t %lu\n", dp->d_ino);

            if ((pwd = getpwuid(statbuf.st_uid)) != NULL) {
                printf("Owner id \t %-8d\n", statbuf.st_uid);
                printf("Owner name \t %-8.8s\n", pwd->pw_name);
            }
            if ((grp = getgrgid(statbuf.st_gid)) != NULL) {
                printf("Group id \t %-8d\n", statbuf.st_gid);
                printf("Group name \t %-8.8s\n", grp->gr_name);
            }
            printf("File size \t %9jd\n", (intmax_t)statbuf.st_size);
            printf("Permissions \t %10.10o\n", statbuf.st_mode);
        }
    } while(dp != NULL);

    closedir(dir);

}

int main(int argc, char * argv[])
{
    if(argv[1] != NULL) {
        printf("Info about: %s\n", argv[1]);
        getStat(argv[1]);
    } else {
        puts("no argument given");
    }

    return 0;
}