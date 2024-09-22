/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Processes - part1.c
 * Ghobrial, Mina Youhanna Helmi / 2214988
 * Rouabah, Abdelmounaim / 2211513
*/

#include "libprocesslab/libprocesslab.h"

int waitChildTotal() {
    int status;
    int nbCountChild = 0;
    while (wait(&status) > 0) {
        if (WIFEXITED(status)) {
            nbCountChild += WEXITSTATUS(status);
            nbCountChild ++;
        }
    }
    return nbCountChild;
}

void question1() {

    int nbCount = 0;
    int status;

	//proc de question1, main
    registerProc(getpid(), getppid(), 0, 0);

	//enfant1.1
    if (fork() == 0) { 
        registerProc(getpid(), getppid(), 1, 1);
        int nbCount = 0;
        if (fork() == 0) {
            registerProc(getpid(), getppid(), 2, 1);
            _exit(0);
        }
        nbCount += waitChildTotal();
        _exit(nbCount);
    }
    
	//enfant 1.2
    if (fork() == 0) {
        registerProc(getpid(), getppid(), 1, 2);
        int nbCount = 0;
        if (fork() == 0) {
            registerProc(getpid(), getppid(), 2, 2);
            _exit(0);
        }
        if (fork() == 0) {
            registerProc(getpid(), getppid(), 2, 3);
            _exit(0);
        }
        nbCount += waitChildTotal();
        _exit(nbCount);
    }
    
	//enfant 1.3
    if (fork() == 0) {
        registerProc(getpid(), getppid(), 1, 3);
        int nbCount = 0;
        if (fork() == 0) {
            registerProc(getpid(), getppid(), 2, 4);
            _exit(0);
        }
        nbCount += waitChildTotal();
        _exit(nbCount);
    }


	//enfant 1.4
    if (fork() == 0) {
        registerProc(getpid(), getppid(), 1, 4);
        int nbCount = 0;
        if (fork() == 0) {
            registerProc(getpid(), getppid(), 2, 5);
            _exit(0);
        }
        if (fork() == 0) {
            registerProc(getpid(), getppid(), 2, 6);
            _exit(0);
        }
        if (fork() == 0) {
            registerProc(getpid(), getppid(), 2, 7);
            _exit(0);
        }
        nbCount += waitChildTotal();
        _exit(nbCount);
    }

    nbCount = waitChildTotal();
    
    //le pere ne sera pas compte (processus du question1())
    printf("nb enfant cree : %d\n", nbCount);
    printProcRegistrations();
    execlp("ls", "ls", "-l", NULL);
    perror("execlp na pas marche");
}

