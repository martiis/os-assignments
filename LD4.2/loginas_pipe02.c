/* Martynas Sudintas IF-2/10 marsud */
/* Failas: loginas_pipe02.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <ftw.h>

int main( int argc, char * argv[] )
{
	if (argc != 2)
	{
		printf("Nenurodytas failas!\n");
		return 0;
	}

	struct stat buffer;
	int size;

	int fd[2];
	pid_t pid, x;
	int status;

	int dskr = open(argv[1], O_RDONLY);
	if (dskr < 0)
	{
		perror(argv[1]);
		return 0;
	}

	if (stat(argv[1], &buffer) != 0)
	{
		printf("Klaida\n");
	}
	size = buffer.st_size;
	char fileBuf[size];
	read(dskr, fileBuf, size);
	close(dskr);

	if (pipe(fd) == -1)
	{
		fprintf(stderr, "Nepavyko sukurti programinio kanalo !\n");
		return 0;
	}
	pid = getpid();
	if (write(fd[1], &fileBuf, size) != sizeof(fileBuf))
	{
		fprintf(stderr, "Klaida rasant");
		return 0;
	}
	pid = fork();
	if (pid == 0)
	{
		char readBuf[size];
		sleep(1);
		read(fd[0], &readBuf, size);
		printf("Failo turinys: %s\n", readBuf);
		return 1;
	}
	else if (pid == -1)
	{
		fprintf(stderr, "Nepavyko sukurti vaiko !\n");
		return 0;
	}
	else
	{
		printf("(tevas) Mano PID: %ld\n", getpid());
		x = wait(&status);
		return 1;
	}

}
