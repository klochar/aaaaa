/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part1.c
 * Ghobrial, Mina Youhanna Helmi / 2214988
 * Rouabah, Abdelmounaim / 2211513
*/
#include "challenges_part1.h"

void process_directory(const char *dir_path, int parent_pid, int level) {
    DIR *dir;
    struct dirent *entry;
    pid_t pid = getpid();

    // Ouvrir le répertoire
    if ((dir = opendir(dir_path)) == NULL) {
        perror("opendir");
        _exit(1);
    }

    // Préparation pour écrire dans le fichier challenges_output.txt
    int output_file = open("challenges_output.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (output_file < 0) {
        perror("open");
        _exit(1);
    }

    // Informations du répertoire
    dprintf(output_file, "Data 1: Path: %s\n", dir_path);
    dprintf(output_file, "Data 2: PID: %d\n", pid);
    dprintf(output_file, "Data 3: PPID: %d\n", parent_pid);
    dprintf(output_file, "Files:\n");

    // Parcourir le répertoire
    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            // C'est un sous-répertoire : on crée un processus enfant
            pid_t child_pid = fork();
            if (child_pid == 0) {
                // Processus enfant
                process_directory(full_path, pid, level + 1);
                _exit(0);
            } else {
                // Attendre la fin du processus enfant
                wait(NULL);
            }
        } else if (entry->d_type == DT_REG) {
            // C'est un fichier : vérifier si c'est un fichier texte
            if (strstr(entry->d_name, ".txt") != NULL) {
                dprintf(output_file, "  %s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    close(output_file);
}

int waitChildTotal() {
    int status, total = 0;
    while (wait(&status) > 0) {
        if (WIFEXITED(status)) {
            total += WEXITSTATUS(status);
        }
    }
    return total;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Initialiser le fichier challenges_output.txt
    int output_file = open("challenges_output.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (output_file < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(output_file);

    // Lancer le traitement à partir du répertoire racine fourni en argument
    process_directory(argv[1], getppid(), 0);

    // Afficher le nombre total d'enfants
    int total_files = waitChildTotal();
    printf("Nombre total de fichiers texte: %d\n", total_files);

    return 0;
}

