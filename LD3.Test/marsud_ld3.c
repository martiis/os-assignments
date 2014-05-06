/* Martynas Sudintas KTU marsud */
/* Failas: marsud_ld3.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int openFile(char * fv)
{
    int dskr = open(fv, O_RDONLY);
    if(dskr == -1) {
        printf("Failed to open file: %s\n", fv);
        exit(1);
    }
    return dskr;
}

void closeFile(int dskr)
{
    int result = close(dskr);
    if(result == -1) {
        perror("close");
        exit(1);
    }
}

void init(char * fv, int nbyte)
{
    //For statistics
    time_t start = time(0);
    //->>INIT
    //
    int fileDskr = openFile(fv);
    struct stat mystat;
    void *pmap;

    if(fstat(fileDskr, &mystat) < 0) {
        perror("fstat");
        closeFile(fileDskr);
        exit(1);
    }

    pmap = mmap(0, mystat.st_size, PROT_READ, MAP_SHARED, fileDskr, 0);

    if(pmap == MAP_FAILED) {
        perror("mmap");
        closeFile(fileDskr);
        exit(1);
    }

    //NOW HOW TO READ?!?

    //->END
    time_t end = time(0);

    printf("\nDone in %ldms\n", (end - start));
}

int main(int argc, char *argv[])
{
    if(argc > 3) {
        puts("Too much arguments.");
    } else if(argc < 3) {
        puts("Not enough arguments.");
    } else {
        init(argv[1], atoi(argv[2]));
    }
    return 0;
}