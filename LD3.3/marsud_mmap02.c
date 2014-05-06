/* Martynas Sudintas KTU marsud */
/* Failas: marsud__mmap02.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//TODO: make it WORK
void init(char * toRead, char * toWrite)
{
    int fd;
    int fd2;
    struct stat mystat;
    struct stat mystat2;
    void * pmap;
    void * pmap2;

    fd = open(toRead, O_RDONLY);
    if(fd == -1) {
        perror("open");
        exit(1);
    }
    fd2 = open(toWrite, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1) {
        perror("open2");
        exit(1);
    }

    if(fstat(fd, &mystat) < 0) {
        perror("fstat");
        close(fd);
        exit(1);
    }
    if(fstat(fd2, &mystat2) < 0) {
        perror("fstat2");
        close(fd2);
        exit(1);
    }

    pmap = mmap(0, mystat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    pmap2 = mmap(0, mystat2.st_size, PROT_WRITE, MAP_SHARED, fd2, 0);

    if(pmap == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }
    if(pmap2 == MAP_FAILED) {
        perror("mmap2");
        close(fd2);
        exit(1);
    }

    memcpy(pmap2, pmap, mystat.st_size);

    close(fd);
    close(fd2);
}

int main(int argc, char * args[])
{
    if(argc > 3) {
        printf("To much arguments given. Expected 2\n");
    } else if(argc < 3) {
        printf("Not enough arguments. Expected 2\n");
    } else {
        init(args[1], args[2]);
    }
    return 0;
}