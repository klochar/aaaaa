/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Processes - part2.c
 * Ghobrial, Mina Youhanna Helmi / 2214988
 * Rouabah, Abdelmounaim / 2211513
*/

#include "./libprocesslab/libprocesslab.h"

#define m 1000000
// question2 calcule la somme des m premiers nombres naturels 1+2+...+m

// nb est le nombre de threads qui vont contribuer au calcul
#define nb 8

//tableau somme est utilisé pour le calcul des sommes patielles par les threads
long somme[nb];


// fonction exécutée par chaque thread créé
void* contribution(void*p)
{
    long no = (long)p;
    long start = (no * m / nb) + 1;
    long end = (no + 1) * m / nb;
    somme[no] = 0;

    for (long i = start; i <= end; i++) {
        somme[no] += i;
    }

  return NULL;
}


void question2( )
{
    pthread_t threads[nb]; 

    for (long i = 0; i < nb; i++) {
        pthread_create(&threads[i], NULL, contribution, (void*)i); 
    }

    for (int i = 0; i < nb; i++) {
        pthread_join(threads[i], NULL); 
    }

    long total = 0;
    for (int i = 0; i < nb; i++) {
        total += somme[i]; 
    }

    long longSommationM = m;
    long shouldBe = longSommationM * (longSommationM + 1) / 2;
    printf("calculated by threads: %ld\n", total);
    printf("should be: %ld\n", shouldBe); 
    
}

