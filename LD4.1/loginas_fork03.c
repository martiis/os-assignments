/* Martynas Sudintas IF-2/10 marsud */
/* Failas: loginas_fork03.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void fork_test(pid_t pid)
{
	switch(pid)
	{
	case -1:
		printf("Fork klaida!\n");
		break;
	case 0:
		printf("Vaikas. \"%ld\" -> \"%ld\"\n", getppid(), getpid());
		break;
	default:
		printf("Tevas. \"%ld\" -> \"%ld\"\n", getppid(), getpid());
		break;
	}
}

int main( int argc, char * argv[] )
{
	pid_t f1;
	int st;

	f1 = fork();
	fork_test(f1);

	if (f1 > 0)
	{
		wait(&st);
	}

	system("ps -ef | grep marsud");

	return 1;
}