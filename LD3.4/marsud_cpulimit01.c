/* Martynas Sudintas KTU marsud */
/* Failas: marsud_cpulimit01.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/time.h>

int infinity();
int setLimit(int nuo, int iki);

int setLimit(int nuo, int iki)
{
        struct rlimit rl;
        getrlimit( RLIMIT_CPU, &rl );
        printf( "Get:\tRLIMIT_CPU %ld (soft) %ld (hard)\n", rl.rlim_cur, rl.rlim_max );

        rl.rlim_cur = nuo;
        rl.rlim_max = iki;

        setrlimit( RLIMIT_CPU, &rl );
        getrlimit( RLIMIT_CPU, &rl );
        printf( "Set:\tRLIMIT_CPU %ld (soft) %ld (hard)\n", rl.rlim_cur, rl.rlim_max );

}

int infinity()
{
	int sk;
	sk = 0;
	while(1) {
		sk = sk + 1;
		printf("%d\n", sk);
	}
	return 1;
}

int main(int argc, char *argv[])
{
	setLimit(0,5);
	setLimit(0,0);
	infinity();
	return 0;
}
