/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int *data;
    int n_rows;
    int n_cols;
    int stride_rows;
    int stride_cols;
    int offset;
} Matrix;

//Criação de matrizes
Matrix create_matrix    (int *data, int n_rows, int n_cols);
Matrix zeros_matrix     (int n_rows, int n_cols);
Matrix full_matrix      (int n_rows, int n_cols, int value);
Matrix i_matrix         (int n);
Matrix tile_matrix      (Matrix matrix, int reps);

//Manipulação de dimensões
Matrix transpose        (Matrix matrix);
Matrix reshape          (Matrix matrix, int new_n_rows, int new_n_cols);
Matrix slice            (Matrix a_matrix, int rs, int re, int cs, int ce);

//Operações aritméticas
Matrix add              (Matrix matrix_1, Matrix matrix_2);
Matrix sub              (Matrix matrix_1, Matrix matrix_2);
Matrix division         (Matrix matrix_1, Matrix matrix_2);
Matrix mul              (Matrix matrix_1, Matrix matrix_2);

//Acesso de elementos
int get_element         (Matrix matrix, int ri, int ci);
void put_element        (Matrix matrix, int ri, int ci, int elem);
void print_matrix       (Matrix matrix);

//Funções de agregação
int min                 (Matrix matrix);
int max                 (Matrix matrix);
int argmin              (Matrix matrix);
int argmax              (Matrix matrix);

#endif
