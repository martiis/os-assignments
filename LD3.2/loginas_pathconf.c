/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_pathconf.c */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int filenameLength()
{
    int result;
    if ( (result = pathconf("/", _PC_NAME_MAX)) != -1 ) {
        printf("_PC_NAME_MAX is %d\n", result);
        return result;
    } else {
        return 0;
    }
}

int pathLength()
{
    int result;
    if( (result = pathconf("/", _PC_PATH_MAX)) != -1 ) {
        printf("_PC_PATH_MAX is %d\n", result);
        return result;
    } else {
        return 0;
    }
}

main()
{
  filenameLength();
  pathLength();
}