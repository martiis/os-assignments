/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_fork01.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void forkChild(pid_t f)
{
	switch(f)
	{
		case -1:
			perror("fork");
			exit(1);
		case 0:
			puts("child");
			pid_t f2 = fork();

			if(f2 == 0)
			{
				puts("grandchildren");
			}

			exit(0);
		default:
			puts("parent");			

			exit(0);
	}
}

int main(int argc, char * argv[])
{
	pid_t f = fork();
	forkChild(f);
}