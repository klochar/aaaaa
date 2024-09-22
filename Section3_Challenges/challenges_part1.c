/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part1.c
 * Ghobrial, Mina Youhanna Helmi / 2214988
 * Rouabah, Abdelmounaim / 2211513
*/
#include "challenges_part1.h"

int counterNbTxt(const char *dirpath) {
    struct dirent *fileEntry;
    DIR *dir = opendir(dirpath);
    if (!dir) return 0;

    int txtCounter = 0;
    while ((fileEntry = readdir(dir)) != NULL) {
        if (fileEntry->d_type == DT_REG && strstr(fileEntry->d_name, ".txt")) {
            txtCounter++;
        }
    }
    closedir(dir);
    return txtCounter;
}

void proceDir(const char *dirpath, FILE *output, pid_t parent_pid) {
    struct dirent *entry;
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("error opendir");
        return;
    }
    pid_t pid = getpid();
    int txt_count = counterNbTxt(dirpath);

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
            pid_t child_pid = fork();
            if (child_pid == 0) {

                char subdir[1024];
                snprintf(subdir, sizeof(subdir), "%s/%s", dirpath, entry->d_name);
                proceDir(subdir, output, pid); 
                exit(0);
            }
        }
    }


    closedir(dir);
    while (wait(NULL) > 0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *root_dir = argv[1];


    FILE *output = fopen("challenges_output.txt", "w");
    if (!output) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    proceDir(root_dir, output, getpid());

    fclose(output);
    
    return 0;
}
