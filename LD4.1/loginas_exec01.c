/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_fork01.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	if(argc == 2) {
		int arg = atoi(argv[1]);
		pid_t pid = getpid();
      	pid_t ppid = getppid();
		printf("PID: %d\t PPID: %d\t ARG: %d\n", pid, ppid, arg);
			
		if(arg > 0)
		{
			--arg;
			char msg[3];
			sprintf(msg, "%d", arg);
			execl(
			     "/home/martynas/Projects/os-assignments/LD4.1/a.out",
			     "a.out",
			     msg,
			     NULL
			);
		}

	} else {
		puts("invalid number of args. expected only 1.");
	}	
	return 0;
}
