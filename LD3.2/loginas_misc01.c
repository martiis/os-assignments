/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_misc01.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    mkdir("./folderis", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    puts("Buvo sukurta nauja direktorija.");
    return 0;
}