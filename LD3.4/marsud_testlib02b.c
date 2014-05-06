/* Vardenis Pavardenis KTU loginas */
/* Failas: loginas_testlib02b.c */

#include <stdio.h>
#include "marsud_testlib02.h"

double marsud_libvar02;

int marsud_libfunc02( const char *s ){
    printf( "Dynamic library for testing, %s\n", __FILE__ );
    printf( "\tparameter: \"%s\"\n", s );
    printf( "\tlib variable = %f\n", marsud_libvar01 );
    return 0;
}
