/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_getcwd02.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int getCwdTest();

int getCwdTest()
{
    //1
   char *cwd;
   cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
   puts(cwd);
   //2
   int dskr = open(cwd, O_RDONLY);
   printf("Deskriptorius: %d\n", dskr);
   //3
   chdir("/tmp");
   cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
   puts(cwd);
   //4
   fchdir(dskr);
   cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
   puts(cwd);
   return 1;
}

int main()
{
   getCwdTest();
   return 0;
}
