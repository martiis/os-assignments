/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_fork02.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void forkChild(pid_t f)
{
    int st;
    pid_t pid;

	switch(f)
	{
		case -1:
			perror("fork");
			exit(1);
		case 0:
			puts("child, waiting");
			wait(&st);
			pid = getppid();
			printf("new parent pid: %d\n", pid);
			exit(0);
		default:
		    pid = getpid();
            printf("parent pid: %d\n", pid);
			exit(0);
	}
}

int main(int argc, char * argv[])
{
	pid_t f = fork();
	forkChild(f);
}
