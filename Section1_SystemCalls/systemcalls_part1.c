/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * SystemCalls - part1.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main () {
    // TODO
	int fichier = open("systemcalls_output2.txt", O_TRUNC | O_WRONLY);
	printf("Saisissez votre texte suivi de CTRL-D :\n");
	char buf[1];
    	ssize_t bytesRead;
	
	while ((bytesRead = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        
       		if (write(fichier, buf, bytesRead) != bytesRead) {
            		perror("Appel système open a échoué");
            		close(fichier);
            		return 1;
        	}
    	}
	if (bytesRead == -1) {
        	perror("Erreur lors de la lecture");
    	}
	close(fichier);
    	return 0;
}

