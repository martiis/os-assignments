/* Martynas Sudintas KTU marsud */
/* Failas: loginas_signal02.c */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdlib.h>

static int received_sig1 = 0;
static int received_sig2 = 0;

void il_catch_USR1( int );       /* signalo apdorojimo f-ja */
void il_catch_USR2( int );       /* signalo apdorojimo f-ja */
int il_child( void );            /* vaiko proceso veiksmai */
int il_parent( pid_t pid );      /* tevo proceso veiksmai */

int il_child( void ){
   sleep( 1 );
   printf( "\tchild: my ID = %d\n", getpid() );
   while( 1 ) {
      if ( received_sig1 == 1 ){
          printf( "\tchild: Received usr1 signal from parent!\n" );
          system("who");
          printf( "\tchild: sending USR2 signal to parent\n" );
          kill(getppid(), SIGUSR2);
          received_sig1 = 0;
          return 0;
      }
   }

}

int il_parent( pid_t pid ){
   printf( "parent: my ID = %d\n", getpid() );
   printf( "parent: my child's ID = %d\n", pid );
   sleep( 3 );
   kill( pid, SIGUSR1 );
   printf( "parent: Signal was sent\n" );
   wait(NULL);
   while(1) {
        if(received_sig2 == 1) {
            printf( "parent: Received usr2 signal from child!\n" );
            printf( "parent: killing child!\n" );
            kill(pid, SIGKILL);
            break;
        }
   }
   
   sleep(5);
   printf( "parent: exiting.\n" );
   return 0;
}

void il_catch_USR1( int snum ) {
   received_sig1 = 1;
}

void il_catch_USR2( int snum ) {
   received_sig2 = 1;
}


int main( int argc, char **arg ){

   pid_t  pid;

   signal(SIGUSR1, il_catch_USR1);
   signal(SIGUSR2, il_catch_USR2);
   switch( pid = fork() ){
      case 0: /* fork() grazina 0 vaiko procesui */
         il_child();
         break;
      default: /* fork() grazina vaiko PID tevo procesui */
         il_parent(pid);
         break;
      case -1: /* fork() nepavyko */
         perror("fork");
         exit(1);
   }
   exit(0);
}

