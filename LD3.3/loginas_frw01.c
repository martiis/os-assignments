/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_frw01.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Nukopijuokite loginas_rw01.c į loginas_frw01.c ir pakeiskite, kad vietoj open() būtų naudojama fopen(), vietoj close() – fclose(), vietoj read() – fread(), vietoj write() – fwrite().
Išbandykite naują programą. Turėtų gautis toks pat rezultatas.
Kuo skiriasi fgetc() ir getc(): ?
 */

int doTest();

int doTest(char * fv1, char * fv2, int siz)
{
    //OPENING
    FILE *dskrFV1 = fopen(fv1, "r");
    FILE *dskrFV2 = fopen(fv2, "wb");

    if(dskrFV1 == NULL) {
        printf("Failed to open a file %s\n", fv1);
        exit(1);
    }
    if(dskrFV2 == NULL) {
        printf("Failed to create or trunicate a file: %s\n", fv2);
        exit(1);
    }
    //READING
    char buf[siz+1];
    fread((void *) buf, siz, 1, dskrFV1);
    //WRITING
    fwrite((void *)buf, siz, 1, dskrFV2);
    //CLOSING
    fclose(dskrFV1);
    fclose(dskrFV2);
    return 0;
}

int main(int argc, char * argv[])
{
    if(argc < 4) {
        puts("Not enough args");
    } else if(argc > 4) {
        puts("Too much args");
    } else {
        doTest(argv[1], argv[2], atoi(argv[3]));
    }

   return 0;
}
