/* Martynas Sudintas KTU marsud */
/* Failas: marsud_nice01.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>

void setPriotity(int pr) {
    nice(pr);
}

int infinity()
{
    int sk=0;
    while(1) {
        sk++;
        printf("WOO");
        if(sk==1000000) {
            break;
        }
    }
    return 1;
}

// -> END cpulimit01.c

int main(int argc, char *argv[]) {
    if(argc != 2) {
        puts("Invalid number of arguments");
    } else {
        int priority = atoi(argv[1]);
        printf("Setting priority: %d\n", priority);
        //case 1: without nice
        time_t case1Now = time(0);
        infinity();
        time_t case1End = time(0);
        time_t took1 = case1End - case1Now;
        //case 2: with nice
        setPriotity(priority);
        time_t case2Now = time(0);
        infinity();
        time_t case2End = time(0);
        time_t took2 = case2End - case2Now;
        //RESULTS
        printf("CASE1: \nStarted %ld\t Ended %ld\t Took %ld", case1Now, case1End, took1);
        printf("CASE2: \nStarted %ld\t Ended %ld\t Took %ld\n", case2Now, case2End, took2);
    }
    return 0;
}