/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Processes - part1.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include "libprocesslab/libprocesslab.h"


void question1()
{
	//todo
	// Create the root process (level 0)
    pid_t level0 = getpid();
    printf("Level 0, PID: %d\n", level0);
    registerProc(level0, 0, 0, 0); // Root process registration

    // Level 1 processes
    pid_t level1_1, level1_2, level1_3, level1_4;

    if ((level1_1 = fork()) == 0) {
        // Level 2.1 process
        pid_t level2_1;
        printf("Level 1.1, PID: %d\n", getpid());
        registerProc(getpid(), getppid(), 1, 1);

        if ((level2_1 = fork()) == 0) {
            printf("Level 2.1, PID: %d\n", getpid());
            registerProc(getpid(), getppid(), 2, 1);
        } else {
            wait(NULL); // Wait for child to finish
        }

        exit(0); // Exit Level 1.1 process
    } else if ((level1_2 = fork()) == 0) {
        // Level 2.2 and 2.3 processes
        pid_t level2_2, level2_3;
        printf("Level 1.2, PID: %d\n", getpid());
        registerProc(getpid(), getppid(), 1, 2);

        if ((level2_2 = fork()) == 0) {
            printf("Level 2.2, PID: %d\n", getpid());
            registerProc(getpid(), getppid(), 2, 2);
        } else if ((level2_3 = fork()) == 0) {
            printf("Level 2.3, PID: %d\n", getpid());
            registerProc(getpid(), getppid(), 2, 3);
        } else {
            wait(NULL); // Wait for children to finish
        }

        exit(0); // Exit Level 1.2 process
    } else if ((level1_3 = fork()) == 0) {
        // Level 2.4 process
        pid_t level2_4;
        printf("Level 1.3, PID: %d\n", getpid());
        registerProc(getpid(), getppid(), 1, 3);

        if ((level2_4 = fork()) == 0) {
            printf("Level 2.4, PID: %d\n", getpid());
            registerProc(getpid(), getppid(), 2, 4);
        } else {
            wait(NULL); // Wait for child to finish
        }

        exit(0); // Exit Level 1.3 process
    } else if ((level1_4 = fork()) == 0) {
        // Level 2.5, 2.6, and 2.7 processes
        pid_t level2_5, level2_6, level2_7;
        printf("Level 1.4, PID: %d\n", getpid());
        registerProc(getpid(), getppid(), 1, 4);

        if ((level2_5 = fork()) == 0) {
            printf("Level 2.5, PID: %d\n", getpid());
            registerProc(getpid(), getppid(), 2, 5);
        } else if ((level2_6 = fork()) == 0) {
            printf("Level 2.6, PID: %d\n", getpid());
            registerProc(getpid(), getppid(), 2, 6);
        } else if ((level2_7 = fork()) == 0) {
            printf("Level 2.7, PID: %d\n", getpid());
            registerProc(getpid(), getppid(), 2, 7);
        } else {
            wait(NULL); // Wait for children to finish
        }

        exit(0); // Exit Level 1.4 process
    } else {
        wait(NULL); // Wait for all Level 1 processes to finish
    }
}

