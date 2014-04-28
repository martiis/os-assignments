/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_rw01.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
/**
 * Sukurkite programą loginas_rw01.c, kuri:

    atidarytų komandinėje eilutėje nurodytą failą tik skaitymui su open();
    atidarytų kitą komandinėje eilutėje nurodytą failą tik rašymui (sukurtų, jei nėra, išvalytų turinį jei jau yra);
    nukopijuotų iš skaitomo failo į rašomą komandinėje eilutėje nurodytą baitų skiačių (jei tiek baitų nėra – tiek kiek yra, t. y. visą failą) naudojant read() ir write();
    uždarytų abu failus su close().
 */
int doTest();

int doTest(char * fv1, char *fv2, int siz)
{
    //OPENING
    int dskrFV1 = open(fv1, O_RDONLY);
    int dskrFV2 = open(fv2, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(dskrFV1 == -1) {
        printf("Failed to open a file %s\n", fv1);
        exit(1);
    }
    if(dskrFV2 == -1) {
        printf("Failed to create or trunicate a file: %s\n", fv2);
        exit(1);
    }
    //READING
    char buf[siz+1];
    read(dskrFV1,buf, siz);
    //WRITING
    write(dskrFV2, buf, siz);
    //CLOSING
    close(dskrFV1);
    close(dskrFV2);
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
