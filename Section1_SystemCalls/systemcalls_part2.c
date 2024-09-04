/*
 * Ecole Polytechnique Montreal - GIGLL
 * Automne 2024
 * SystemCalls - part2.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void part21 ()
{
    	// TODO
	const char *message1 = "77dbcb01f571f1c32s196c3a7d27f62e (printed using printf)\n";
    	while (*message1) {
        	printf("%c", *message1);
        	message1++;
    	}
	
	const char *message2 = "77dbcb01f571f1c32s196c3a7d27f62e (printed using write)\n";
	write(STDOUT_FILENO, message2, sizeof("77dbcb01f571f1c32s196c3a7d27f62e (printed using write)\n") - 1);
}

void part22 ()
{
    	// TODO
	setvbuf(stdout, NULL, _IONBF, 0);
    	const char *message1 = "77dbcb01f571f1c32s196c3a7d27f62e (printed using printf)\n";
        while (*message1) {
                printf("%c", *message1);
                message1++;
        }
         
        const char *message2 = "77dbcb01f571f1c32s196c3a7d27f62e (printed using write)\n";
	write(STDOUT_FILENO, message2, sizeof("77dbcb01f571f1c32s196c3a7d27f62e (printed using write)\n") - 1);
}

int main (int argc, char* argv[])
{
    
    if (argc!=2)
    {   printf("Le programme a un seul paramètre : 1 ou 2\n");
        return 1;
    }
    switch (atoi(argv[1])) {
         case 1:        part21();
                        break;
         case 2:        part22();
                        break;
        default:        printf(" Le paramètre du programme est invalide\n");
                        return 1;
    }
    return 0;
}
