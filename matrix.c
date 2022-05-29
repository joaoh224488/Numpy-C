/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#include <stdio.h>
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
}

