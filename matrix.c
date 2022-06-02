/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define DEFAULT_STRIDE_COLS 1 // Por padrão, pulará uma coluna 
#define DEFAULT_OFFSET 0      // Por padrão, consideraremos o array do início
#define N_ELEM matrix.n_rows * matrix.n_cols


// CRIAÇÃO DE MATRIZES
Matrix create_matrix(int *data, int n_rows, int n_cols){
    // Inicialização da matriz
    Matrix mat;

    // Inicializando o 'construtor' da struct
    mat.data = data;
    mat.n_rows = n_rows;
    mat.n_cols = n_cols;
    mat.stride_rows = n_cols;
    mat.stride_cols = DEFAULT_STRIDE_COLS;
    mat.offset = DEFAULT_OFFSET;

    return mat;
}

Matrix full_matrix(int n_rows, int n_cols, int value){

    // Criando a lista de dados
    int *list_values;
    int n_elem = n_cols * n_rows;
    list_values = malloc(sizeof(int) * n_elem);

    for (int i = 0; i < n_elem; i++){
        list_values[i] = value;
    }

    // Gerando a matriz

    return create_matrix(list_values, n_rows, n_cols);
}

Matrix zeros_matrix(int n_rows, int n_cols){

    return full_matrix(n_rows, n_cols, 0);
} 

Matrix i_matrix (int n){

    // Criando a lista de dados
    int *list_values;
    int n_elem = n * n;
    list_values = malloc(sizeof(int) * n_elem);

    for (int i = 0; i < n_elem; i++){
        if (i % (n + 1) == 0){
            // Elementos da diagonal principal
            list_values[i] = 1;
        }
        else{
            list_values[i] = 0;
        }
    }

    // Gerando a matriz
    return create_matrix(list_values, n, n);
}
/*
2x3     2 3 4           [2,3,4,5,6,7]               => {[2,3,4],[5,6,7]}
        5 6 7

2x6     2 3 4 2 3 4     [2,3,4,2,3,4,5,6,7,5,6,7]   => {[2,3,4],[2,3,4],[5,6,7],[5,6,7]}
        5 6 7 5 6 7

*/
Matrix tile_matrix(Matrix matrix, int reps){

    // Criando a lista de dados
    int *elements;
    elements = malloc(sizeof(int) * N_ELEM * reps);

    // Variáveis de controle para reordenação do array unidimensional de saída
    int col = 0;
    int j = 0;
    int stride = 0;
    for(int i = 0; i < N_ELEM * reps; i++){

        elements[i] = matrix.data[stride+j];
        j++;
        col++;
        if(j == matrix.n_cols){
            j=0;

            if(col == matrix.n_cols*reps){
                col = 0;
                stride += matrix.n_cols;
            }
        }
    }

    // Gerando a matriz
    return create_matrix(elements, matrix.n_rows, matrix.n_cols*reps);

}

// MANIPULAÇÃO DE DIMENSÕES
Matrix transpose(Matrix matrix){
    // Criando a lista de dados
    int *elements;
    elements = malloc(sizeof(int) * N_ELEM);

    elements[0] = matrix.data[0];

    int j = 0, pos = 0, calc = 0;
    int col = 1, row = 1;

    if(matrix.n_rows == matrix.n_cols){
        calc = matrix.n_rows;
    }
    else{
        calc = matrix.n_cols;
    }

    for(int i = 1; i < N_ELEM; i++){
        pos = row*calc;
        elements[i] = matrix.data[j+col*pos];
        row++;
        if(row == matrix.n_rows){
            row = 0;
            j+=1;
        }
    }

    // Gerando a matriz
    return create_matrix(elements, matrix.n_cols, matrix.n_rows);

}

Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols){

    int orig_q = N_ELEM;
    int new_q = new_n_rows * new_n_cols;

    if(orig_q == new_q){
        Matrix re_mat = matrix;

        re_mat.n_rows = new_n_rows;
        re_mat.n_cols = new_n_cols;
        re_mat.stride_rows = new_n_cols;

        return re_mat;
    }

    else{
        printf("\033[0;31mValue Error\033[96m: cannot reshape array of size %d into shape (%d,%d)\033[0m\n", orig_q, new_n_rows, new_n_cols);
        return matrix;
    }
}


Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce){
    if (rs >= 0 && re <= a_matrix.n_rows && cs >= 0 && ce <= a_matrix.n_cols)
    {
        int row_size, col_size, new_n_elem, *new_data;

        row_size = re - rs;

        col_size = ce - cs;

        new_n_elem = row_size * col_size;

        new_data = malloc(new_n_elem* sizeof(int));

        int new_m_index = 0;
        int r, c; // Variaveis para controlar a linha e coluna lida a cada iteracao
        for (r = rs; r < re; r++){
            for (c = cs; c < ce; c++ ){
                new_data[new_m_index++] = a_matrix.data[r * a_matrix.n_cols + c];
                }
            }
        
        return create_matrix(new_data, row_size, col_size);
        }
        else{
        printf("\033[0;31mIndex Error: index out of range. \033[96mReturning original Matrix\033[0m\n");
        return a_matrix;
    }

}

// OPERAÇÕES ARITMÉTICAS
Matrix add(Matrix matrix_1, Matrix matrix_2){
    // Verificando se matrizes têm as mesmas dimensões
    if(matrix_1.n_rows == matrix_2.n_rows && matrix_1.n_cols == matrix_2.n_cols){
        // Criando a lista de dados
        int *elements;
        int n_elem = matrix_1.n_rows * matrix_1.n_cols;
        elements = malloc(sizeof(int) * n_elem);
        // Preenchendo o array unidimensional de saída com base
        // na soma dos elementos de mesmo índice pertencentes à cada matriz
        for(int i = 0; i < matrix_1.n_rows * matrix_1.n_cols; i++){
            elements[i] = matrix_1.data[i] + matrix_2.data[i];
        }

        // Gerando a matriz
        return create_matrix(elements, matrix_1.n_rows, matrix_1.n_cols);
    }
    else{
        printf("\033[0;31mIndex Error: Both matrices should have the same dimensions. \033[96mReturning -9999 Matrix to represent error\033[0m\n");
        return full_matrix(2, 2, -9999);
    }
}

Matrix sub(Matrix matrix_1, Matrix matrix_2){
    // Verificando se matrizes têm as mesmas dimensões
    if(matrix_1.n_rows == matrix_2.n_rows && matrix_1.n_cols == matrix_2.n_cols){
        // Criando a lista de dados
        int *elements;
        int n_elem = matrix_1.n_rows * matrix_1.n_cols;
        elements = malloc(sizeof(int) * n_elem);
        // Preenchendo o array unidimensional de saída com base
        // na subtração dos elementos de mesmo índice pertencentes à cada matriz
        for(int i = 0; i < matrix_1.n_rows * matrix_1.n_cols; i++){
            elements[i] = matrix_1.data[i] - matrix_2.data[i];
        }

        // Gerando a matriz
        return create_matrix(elements, matrix_1.n_rows, matrix_1.n_cols);

    }
    else{
        printf("\033[0;31mIndex Error: Both matrices should have the same dimensions. \033[96mReturning -9999 Matrix to represent error\033[0m\n");
        return full_matrix(2, 2, -9999);
    }
}

Matrix division(Matrix matrix_1, Matrix matrix_2){
    // Verificando se matrizes têm as mesmas dimensões
    if(matrix_1.n_rows == matrix_2.n_rows && matrix_1.n_cols == matrix_2.n_cols){
        // Criando a lista de dados
        int *elements;
        int n_elem = matrix_1.n_rows * matrix_1.n_cols;
        elements = malloc(sizeof(int) * n_elem);
        // Preenchendo o array unidimensional de saída com base
        // na divisão dos elementos de mesmo índice pertencentes à cada matriz
        for(int i = 0; i < matrix_1.n_rows * matrix_1.n_cols; i++){
/*
    Casos especiais da divisão: 
        1º - denominador 0, resultado 'inf' (usaremos -666 representar),
        2º - numerador e denominador 0, resultado 'nan' (usaremos -777 para representar)
*/
            if(matrix_2.data[i] == 0){
                if(matrix_1.data[i] == 0){
                    elements[i] = -777;
                }
                else{
                    elements[i] = -666;
                }
            }
            else{
                elements[i] = matrix_1.data[i] / matrix_2.data[i];
            }
            
        }

        // Gerando a matriz
        return create_matrix(elements, matrix_1.n_rows, matrix_1.n_cols);
    }
    else{
        printf("\033[0;31mIndex Error: Both matrices should have the same dimensions. \033[96mReturning -9999 Matrix to represent error\033[0m\n");
        return full_matrix(2, 2, -9999);
    }
}

Matrix mul(Matrix matrix_1, Matrix matrix_2){
    // Verificando se matrizes têm as mesmas dimensões
    if(matrix_1.n_rows == matrix_2.n_rows && matrix_1.n_cols == matrix_2.n_cols){
        // Criando a lista de dados
        int *elements;
        int n_elem = matrix_1.n_rows * matrix_1.n_cols;
        elements = malloc(sizeof(int) * n_elem);
        // Preenchendo o array unidimensional de saída com base
        // na multiplicação dos elementos de mesmo índice pertencentes à cada matriz
        for(int i = 0; i < matrix_1.n_rows * matrix_1.n_cols; i++){
            elements[i] = matrix_1.data[i] * matrix_2.data[i];
        }

        // Gerando a matriz
        return create_matrix(elements, matrix_1.n_rows, matrix_1.n_cols);

    }
    else{
        printf("\033[0;31mIndex Error: Both matrices should have the same dimensions. \033[96mReturning -9999 Matrix to represent error\033[0m\n");
        return full_matrix(2, 2, -9999);
    }
}

// ACESSANDO ELEMENTOS
int get_element(Matrix matrix, int ri, int ci){
    if(ri < matrix.n_rows && ci < matrix.n_cols){
        int element = matrix.data[(ri * matrix.n_cols + ci)];

        return element;
    }

    else{
        // Caso os índices de linha e/ou coluna ultrapassem os índices da matriz original,
        // será retornado -999999 para representar o erro 'Index Error'.
        printf("\033[0;31mIndex Error\033[96m: index is out of bounds\033[0m\n");
        return -999999;
    }
}

void put_element(Matrix matrix, int ri, int ci, int elem){
    if(ri < matrix.n_rows && ci < matrix.n_cols){
        matrix.data[(ri * matrix.n_cols + ci)] = elem;
    }

    else{
        // Caso os índices de linha e/ou coluna ultrapassem os índices da matriz original,
        // será retornado uma mensagem de erro.
        printf("\033[0;31mIndex Error\033[96m: index is out of bounds\033[0m\n");
    }
}

void print_matrix(Matrix matrix){

        int index = 0;
        for (int i = 0; i < matrix.n_rows; i++) {

            putchar('\n');

            for (int j = 0 ;j< matrix.n_cols ; j++) {
                printf("%d\t", matrix.data[index++]);
    }
    }
    printf("\n\n");

}

// FUNÇÕES DE AGREGAÇÃO
int min(Matrix matrix){
    int minor = matrix.data[0];

    for(int i = 1; i < N_ELEM; i++){
        if(matrix.data[i] < minor){
            minor = matrix.data[i];
        }
    }

    return minor;
}

int max(Matrix matrix){
    int major = matrix.data[0];

    for(int i = 1; i < N_ELEM; i++){
        if(matrix.data[i] > major){
            major = matrix.data[i];
        }
    }

    return major;
}

int argmin(Matrix matrix){
    int minor_index = 0;

    for(int i = 0; i < N_ELEM; i++){
        if(matrix.data[i] == min(matrix)){
            minor_index = i;
        }
    }

    return minor_index;
}

int argmax(Matrix matrix){
    int major_index = 0;

    for(int i = 0; i < N_ELEM; i++){
        if(matrix.data[i] == max(matrix)){
            major_index = i;
        }
    }

    return major_index;
}

