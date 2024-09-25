/*
 * Ecole Polytechnique Montreal - GIGL
 * Automne 2024
 * Challenges - part2.c
 * Ghobrial, Mina Youhanna Helmi / 2214988
 * Rouabah, Abdelmounaim / 2211513
*/
#include "challenges_part2.h"

Matrix* multiply(Matrix* A, Matrix* B) {
    // printf("A: rows = %d, cols = %d\n", A->rows, A->cols);
    // printf("B: rows = %d, cols = %d\n", B->rows, B->cols);
    if (A->rows <= 0 || A->cols <= 0 || B->cols<=0||B->rows<=0) {
        return NULL;  
    }
    if (A->cols != B->rows) {
        return NULL; 
    }
    Matrix* C = malloc(sizeof(Matrix));
    if (!C) {
        return NULL; 
    }
    C->rows = A->rows;
    C->cols = B->cols;
    C->matrix = malloc(C->rows * sizeof(short*));
    if (!C->matrix) {
        free(C); 
        return NULL;
    }

    for (int i = 0; i < C->rows; i++) {
        C->matrix[i] = malloc(C->cols * sizeof(short));
        if (!C->matrix[i]) {
            for (int j = 0; j < i; j++) {
                free(C->matrix[j]);
            }
            free(C->matrix);
            free(C);
            return NULL;
        }
    }

    for (int i = 0; i < C->rows; i++) {
        for (int j = 0; j < C->cols; j++) {
            C->matrix[i][j] = 0; 
            for (int k = 0; k < A->cols; k++) {
                C->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j]; 
            }
        }
    }

    return C; 
}

Matrix* create_matrix(short rows, short cols) {
    Matrix* mat = malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->matrix = malloc(rows * sizeof(short*));
    for (short i = 0; i < rows; i++) {
        mat->matrix[i] = malloc(cols * sizeof(short));
    }
    return mat;
}

void fill_matrix(Matrix* mat, short values[][mat->cols]) {
    for (short i = 0; i < mat->rows; i++) {
        for (short j = 0; j < mat->cols; j++) {
            mat->matrix[i][j] = values[i][j];
        }
    }
}

void print_matrix(const Matrix* mat) {
    for (short i = 0; i < mat->rows; i++) {
        for (short j = 0; j < mat->cols; j++) {
            printf("%d ", mat->matrix[i][j]);
        }
        printf("\n");
    }
}

// int main(int argc, char*argv[]){

//     Matrix* A = create_matrix(2, 3); 
//     short valuesA[2][3] = {
//         {1, 2, 3},
//         {4, 5, 6}
//     };
//     fill_matrix(A, valuesA);

//     Matrix* B = create_matrix(3, 2); 
//     short valuesB[3][2] = {
//         {7, 8},
//         {9, 10},
//         {11, 12}
//     };
//     fill_matrix(B, valuesB);

//     printf("matrice a :\n");
//     print_matrix(A);
//     printf("matrice b:\n");
//     print_matrix(B);
//     Matrix* C = multiply(A, B);

//     if (C == NULL) {
//         printf("dimension invalide, imopssible multiplicatiion\n");
//     } else {

//         printf("AxB :\n");
//         print_matrix(C);
//     }


//     return 0;
// }
