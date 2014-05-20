/* Vardenis Pavardenis KTU varpav */
/* Failas: loginas_pipe02.c */

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {

   int      fd[2];
   pid_t    pid, x;
   int      status;
   
   if(argc == 2) {
       int dskr = open(argv[1], O_RDONLY);
       char buf[1000];
       read(dskrFV1,buf, 1000);
   } else {
        puts("unexpeted number of arguments. expected 1");
        exit(1);
   }

   if( pipe( fd ) == -1 ){
      fprintf( stderr, "Nepavyko sukurti programinio kanalo !\n" );
      exit( 1 );
   }

   pid = getpid();

   if( write( fd[1], &pid, sizeof( pid ) ) != sizeof( pid ) ){
      fprintf( stderr, "Klaida rasant" );
      exit( 2 );
   }

   pid = fork();

   if( pid == 0 ){
      sleep( 1 );  
      read( fd[0], &pid, sizeof( pid ) );
      printf ( "(vaikas) Tevo proceso ID: %d\n", pid );
      exit( 1 ); 

   }

   else if( pid == -1 ){ 
      fprintf ( stderr, "Nepavyko sukurti vaiko !\n" );
      exit( 4 );
   }

   else{ 
      printf("(tevas) Mano PID: %d\n", getpid() );
      x = wait( &status );
      return 0;

   }

}

