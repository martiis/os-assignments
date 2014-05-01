/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_seek01.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

void init(char * fn)
{
    int dskr = open(fn, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    lseek(dskr, 1024, 0);
    write(dskr, "m", 1);
    close(dskr);
}

int main(int argc, char * argv[])
{
    init("./test/write");
    return 0;
}