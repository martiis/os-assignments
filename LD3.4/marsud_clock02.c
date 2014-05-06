/* Martynas Sudintas KTU marsud */
/* Failas: marsud_clock02.c */
#include <stdio.h>
#include <time.h>

void getUTC()
{
time_t rawtime;
  struct tm * ptm;
  time ( &rawtime );
  ptm = gmtime ( &rawtime );
  printf ("UTC Time\t %2d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min);
}

void getLocal()
{
        time_t rawtime;
        struct tm * timeinfo;

        time (&rawtime);
        timeinfo = localtime (&rawtime);
        printf ("Local Time\t%s", asctime(timeinfo));
}

int main()
{
	getLocal();
	getUTC();
  	return 0;
}
