/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define pattern_stride_cols 1
#define pattern_offset 0

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

void print_matrix(Matrix matrix){

    int n_elem = matrix.n_cols * matrix.n_rows;

    for (int i = 0; i < n_elem; i++){

        if (i % matrix.stride_rows == 0 && i != 0)
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