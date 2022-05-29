/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define pattern_stride_cols 1 // Pulará um por padrão
#define pattern_offset 0      // Consideraremos o array do início por padrão


// Criação de matrizes
Matrix create_matrix(int *data, int n_rows, int n_cols){

    Matrix mat;

    mat.data = data;
    mat.n_rows = n_rows;
    mat.n_cols = n_cols;
    mat.stride_rows = n_cols;
    mat.stride_cols = pattern_stride_cols;
    mat.offset = pattern_offset;

    return mat;
}


Matrix full_matrix(int n_rows, int n_cols, int value){
    // Inicialização da matriz
    Matrix full_mat;

    // Criando a lista de Dados

    int *list_values;
    int n_elem = n_cols * n_rows;
    list_values = malloc(sizeof(int) * n_elem);

    // Evitando problemas com a alocação dinâmica

    if (list_values == NULL){
        printf("full_matrix has failed. Refactor you code and try again.\n");
        exit(1);
    }

    for (int i = 0; i < n_elem; i++){
        list_values[i] = value;
    }

    // Caracterizando a matriz

    full_mat = create_matrix(list_values, n_rows, n_cols);

    //free(list_values);

    return full_mat;
}

Matrix zeros_matrix(int n_rows, int n_cols){

    return full_matrix(n_rows, n_cols, 0);
} 

Matrix i_matrix (int n){

    // Inicialização da matriz
    Matrix i_mat;

    // Criando a lista de Dados

    int *list_values;
    int n_elem = n * n;
    list_values = malloc(sizeof(int) * n_elem);

    // Evitando problemas com a alocação dinâmica

    if (list_values == NULL){
        printf("full_matrix has failed. Refactor you code and try again.\n");
        exit(1);
    }

    for (int i = 0; i < n_elem; i++){
        if (i % (n + 1) == 0){
            list_values[i] = 1;             // Elementos da diagonal principal
        }
        else{
            list_values[i] = 0;
        }
    }

    i_mat = create_matrix(list_values, n, n);

    return i_mat;

}

Matrix tile_matrix(Matrix matrix, int reps){
    Matrix tile;

    int *elements;
    int n_elem = matrix.n_rows * matrix.n_cols;
    elements = malloc(sizeof(int) * n_elem*reps);

    /*
    int line = 0;
    int j = 0;
    for(int i = 0; i < n_elem * reps; i++){
        if(line < matrix.n_cols){
            elements[i] = matrix.data[j];
            j++;
            if(j == matrix.n_cols){
                j = 0;
            }
        }
        line++;
    }
    */

    int j = 0;
    for(int i = 0; i < matrix.n_cols * reps; i++){
        if (j < matrix.n_cols){
            elements[i] = matrix.data[j];
            j++;
            if(j == matrix.n_cols){
                j = 0;
            }
        }

    }

    int k = matrix.n_cols;
    for(int i = matrix.n_cols * reps; i < (matrix.n_cols * reps * 2); i++){
        if(k < n_elem){
            elements[i] = matrix.data[k];
            k++;
            if(k == n_elem){
                k = matrix.n_cols;
            }
        }
    }

    tile = create_matrix(elements, matrix.n_rows, matrix.n_cols*reps);

    return tile;
}

// Manipulação de dimensões

Matrix transpose(Matrix matrix){

    Matrix transp = matrix; // Cópia da struct

    transp.n_rows = matrix.n_cols;

    transp.n_cols = matrix.n_rows;

    transp.stride_rows = matrix.n_rows; // Trocando o número de linhas pelo de colunas,
                                        // o valor do "pulo" será alterado para o de 
                                        // linhas da matriz original.
    return transp;
}


Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols){

    int orig_q = matrix.n_rows * matrix.n_cols;
    int new_q = new_n_rows * new_n_cols;

    if (orig_q != new_q){
        printf("Number of elements doesn't match. Impossible to reshape.\n");
    }
    else{

    Matrix re_mat = matrix;

    re_mat.n_rows = new_n_rows;
    re_mat.n_cols = new_n_cols;
    re_mat.stride_rows = new_n_cols;

    return re_mat;
    }
}

// Acessar elementos

void print_matrix(Matrix matrix){

    int n_elem = matrix.n_cols * matrix.n_rows;

    for (int i = matrix.offset; i < n_elem; i++){

        if (i % matrix.stride_rows == 0 && i != matrix.offset)
            putchar('\n');

        printf("%d ", matrix.data[i]);
    }
    putchar('\n');
    putchar('\n');
}

Matrix zeros_matrix(int n_rows, int n_cols){
    Matrix zeros;

    int *full_zeros;
    int n_elem = n_rows * n_cols;
    full_zeros = malloc(sizeof(int) * n_elem);

    for(int i = 0; i < n_elem; i++){
        full_zeros[i] = 0;
    }

    zeros = create_matrix(full_zeros, n_rows, n_cols);

    return zeros;
}
