/* Martynas Sudintas KTU marsud */
/* Failas: marsud__exit01.c */

#include <stdio.h>
#include <stdlib.h>

void Funkcija1()
{
	puts("This is function one.");
}

void Funkcija2()
{
	puts("This is function two.");
	exit(1);
	puts("After exit");
}
void Funkcija3()
{
	puts("This is function three");
	//abort();
	//puts("after abort");
}

int main(int argc, char *argv[])
{
	atexit(Funkcija1);
	atexit(Funkcija2);
	atexit(Funkcija3);
	puts("This is main function");
	return 0;
}
