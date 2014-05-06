/* Vardenis Pavardenis KTU loginas */
/* Failas: loginas_libtest02.c */

#include <stdio.h>
#include "marsud_testlib02.h"

int main() {
    marsud_libfunc02( "Library test 1" );
    marsud_libvar02 = 5.1;
    marsud_libfunc02( "Library test 2" );
    return 0;
}