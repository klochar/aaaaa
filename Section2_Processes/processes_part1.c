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
	pid_t level0 = getpid();
	//registerProc( pid_t pid, pid_t ppid, int procLevel, int procNum);
	registerProc(level0, getppid(), 0, 0);
	printf("Level 0, PID: %d\n", level0);
	//enfant
	pid_t level1_1, level1_2, level1_3, level1_4;
	if((level1_1=fork())==0){
		//on est dans l enfant 1.1
		registerProc(level1_1, getppid(), 1, 1);
		printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
		pid_t level2_1;
		if((level2_1=fork())==0){
			//on est enfant 2.1
			registerProc(level2_1, getppid(), 2, 1);
			printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
			_exit(0);
		}else {
			wait(NULL);
		}
		_exit(0);
	}else if((level1_2=fork())==0){
		//on est dabs enfant 1.2
		registerProc(level1_2, getppid(), 1, 2);
		printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
		pid_t level2_2, level2_3;
		if((level2_2=fork())==0){
			//on est dans enfant 2.2
			registerProc(level2_2, getppid(), 2, 2);
			printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
                        _exit(0);
		} else if((level2_3=fork())==0){
			//on est dans enfant 2.3
			registerProc(level2_3, getppid(), 2, 3);
			printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
			_exit(0);
		} else {
			while(wait(NULL)>0);
		}
		_exit(0);
	}else if((level1_3=fork())==0){
		//on est dabs enfant 1.3
		registerProc(level1_3, getppid(), 1, 3);
		pid_t level2_4;
		printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
		if((level2_4=fork())==0){
			registerProc(level2_4, getppid(), 2, 4);
			printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
                        _exit(0);
		} else {
			wait(NULL);
		}
		_exit(0);
	}else if((level1_4=fork())==0){
		//on est dabs enfant 1.2
		registerProc(level1_4, getppid(), 1, 4);
		pid_t level2_5,level2_6,level2_7;
		printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
		if((level2_5=fork())==0){
			registerProc(level2_5, getppid(), 2, 5);
			printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
                        _exit(0);
		} else if((level2_6=fork())==0) {
			registerProc(level2_6, getppid(), 2, 6);
			printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
                        _exit(0);
		} else if((level2_7=fork())==0){
			registerProc(level2_7, getppid(), 2, 7);
			printf("je suis :%d et mon pere est :%d\n",getpid(),getppid());
                        _exit(0);
		} else {
			while(wait(NULL)>0);
		}
		_exit(0);
	}else{
		while(wait(NULL)>0);
	}
	
}

