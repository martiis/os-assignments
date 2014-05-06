/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_aio01.c */

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <aio.h>
static const int bufferSize = 1048576;

int rd;
// ---------------->
int ps_test_open(const char *name, int oflag, ...){
    int dskr;
    dskr = open( name, oflag );
    if( dskr == -1 ){
        perror( name );
        exit(1);
    }
    if(__INCLUDE_LEVEL__ == 0)
        printf( "dskr = %d\n", dskr );
    return dskr;
}
int ps_test_close(int fd){
    int rv;
    rv = close( fd );
    if( rv != 0 ) perror ( "Klaida iskvietus close() funkcija" );
    else if (__INCLUDE_LEVEL__ == 0) puts( "closed" );
    return rv;
}
// ---------------->
int ps_test_aio_read_start( const int d, struct aiocb *aiorp, void *buf,
    const int count ){
    int rv = 0;
    memset( (void *)aiorp, 0, sizeof( struct aiocb ) );
    aiorp->aio_fildes = d;
    aiorp->aio_buf = buf;
    aiorp->aio_nbytes = count;
    aiorp->aio_offset = 0;
    rv = ps_test_aio_read( aiorp );
    return rv;
}
int ps_test_aio_read(struct aiocb *aiocbp){
    int rv;
    if( (rv = aio_read(aiocbp)) == -1 ){
        perror( "aio_read failed" );
        abort();
    }
    return rv;
}
int ps_test_dummy( const void *data, int n ){
    int i, cnt = 0;
    for( i = 0; i < n; i++ )
        if( ((char*)data)[i] == '\0' ) cnt++;
    printf( "Number of '0' in data: %d\n", cnt );
    return 1;
}
int ps_test_aio_read_waitcomplete( struct aiocb *aiorp ){
    const struct aiocb *aioptr[1];
    int rv;
    aioptr[0] = aiorp;
    rv = ps_test_aio_suspend( aioptr, 1, NULL );

    rv = ps_test_aio_return( aiorp );
    printf( "AIO complete, %d bytes read.\n", rv );
    return 1;
}
int ps_test_aio_suspend(const struct aiocb * const list[], int nent, const struct timespec *timeout){
    int rv;
    if( (rv = aio_suspend(list, nent, timeout)) == 0 ){
        perror( "aio_suspend failed" );
        abort();
    }
    return rv;
}
int ps_test_aio_return(struct aiocb *aiocbp){
    int rv;
    if ( (rv = aio_return(aiocbp) ) == -1) {
        perror("aio_return failed");
        abort();
    }
    return rv;
}

// ------------------->
//
int ps_read_bytes(int desc, struct aiocb *block, char *buf, int bufOffset, int bytes){
    memset((void*)block, 0, sizeof(struct aiocb));
    block->aio_fildes = desc;
    block->aio_buf = buf + bufOffset;
    block->aio_nbytes = bytes;
    block->aio_offset = 0;
    if(ps_test_aio_read(block) != 0){
        printf("Klaida skaitymo pradzioje\n");
        return -1;
    }
    return 0;
}

int ps_read_wait(struct aiocb *block){
    const struct aiocb *temp[1];
    temp[0] = block;
    if(ps_test_aio_suspend(temp, 1, NULL) != 0){
        printf("Klaida skaitymo pabaigoje\n");
        return -1;
    }
    return ps_test_aio_return(block);
}

void ps_exit(int code){
    ps_test_close(rd);
    exit(code);
}

int main(){
    struct aiocb block;
    char *buf;
    int n = 0, t;
    buf = malloc(bufferSize);
    rd = ps_test_open("/dev/urandom", O_RDONLY);
    if(rd == -1){
        printf("Klaida atidarinejant faila\n");
        ps_exit(1);
    }
    while(n < bufferSize){
        if(ps_read_bytes(rd, &block, buf, n, bufferSize - n) != 0)
            ps_exit(1);
        t = ps_read_wait(&block);
        if(t > 0){
            n += t;
            printf("Perskaityta %d baitu\n", n);
        }else
            ps_exit(1);
    }
    ps_exit(0);
    return 0;
}
