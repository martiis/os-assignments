/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_fork01.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

/*
     / labas...
   -
  /  \ labas...
-- 
  \  / labas...
   -
     \ labas...
*/
int main(int argc, char * argv[])
{
	fork();
	fork();
	puts("labas as krabas.");
}