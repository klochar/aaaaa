/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part1.c
 * Ghobrial, Mina Youhanna Helmi / 2214988
 * Rouabah, Abdelmounaim / 2211513
*/
#include "challenges_part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int txtCounterTotal = 0; 

int counterNbTxt(const char *dirpath) {
    struct dirent *fileEntry;
    DIR *dir = opendir(dirpath);
    if (!dir) return 0;

    int txtCounterInThisDir = 0;
    while ((fileEntry = readdir(dir)) != NULL) {
        if (fileEntry->d_type == DT_REG && strstr(fileEntry->d_name, ".txt")) {
            txtCounterInThisDir++;
        }
    }
    closedir(dir);
    
    //txtCounterTotal += txtCounterInThisDir;

    return txtCounterInThisDir;
}

void proceDir(const char *dirpath, FILE *output, pid_t parent_pid, int pipe_fd[2]) {
    struct dirent *entry;
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("error opendir");
        return;
    }
    pid_t pid = getpid();
    int txt_count = counterNbTxt(dirpath);
    // txtCounterTotal+=txt_count;
    //printf("%d\n",txt_count);
    int total_txt_in_subdirs=0;
    fprintf(output, "nb .txt file in %s: %d\n", dirpath, txt_count);
    fprintf(output, "Data 1: %s\n", dirpath); 
    fprintf(output, "Data 2: %d\n", pid);
    fprintf(output, "Data 3: %d\n", parent_pid); 
    fprintf(output, "Files:\n");
    rewinddir(dir); 
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".txt")) {
            fprintf(output, "%s\n", entry->d_name);
        }
    }
    rewinddir(dir); 
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            int sub_pipe_fd[2];
            pipe(sub_pipe_fd);
            pid_t child_pid = fork();
            if (child_pid == 0) {
                close(sub_pipe_fd[0]);
                char subdir[1024];
                snprintf(subdir, sizeof(subdir), "%s/%s", dirpath, entry->d_name);
                proceDir(subdir, output, pid, sub_pipe_fd);
                exit(0);
            }else {  
                close(sub_pipe_fd[1]);
                int child_txt_count;
                read(sub_pipe_fd[0], &child_txt_count, sizeof(int));
                total_txt_in_subdirs += child_txt_count;
                close(sub_pipe_fd[0]);
            }
        }
    }

    closedir(dir);
    while (wait(NULL) > 0);
    int total_txt = txt_count + total_txt_in_subdirs;
    write(pipe_fd[1], &total_txt, sizeof(int));
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipe_fd[2];
    pipe(pipe_fd);

    const char *root_dir = argv[1];

    FILE *output = fopen("challenges_output.txt", "w");
    if (!output) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    proceDir(root_dir, output, getpid(), pipe_fd);

    int total_txt_files;
    close(pipe_fd[1]);  // Fermer le côté écriture du pipe
    read(pipe_fd[0], &total_txt_files, sizeof(int));  // Lire le résultat final
    close(pipe_fd[0]);

    printf("Total number of .txt files: %d\n", total_txt_files);
    fprintf(output, "Total number of .txt files: %d\n", total_txt_files);

    fclose(output);
    return 0;
}

