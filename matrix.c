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

    // Variáveis de controle para ordenação do array unidimensional de saída
    int count_col = 0, read_m = 0, row = 0, col = 0;
 
    for(int i = 0; i < N_ELEM * reps; i++){

        read_m = row * matrix.stride_rows + col * matrix.stride_cols + matrix.offset;
        elements[i] = matrix.data[read_m];

        col++;
        count_col++;

        if(col == matrix.n_cols){
            col = 0;

            if(count_col == matrix.n_cols * reps){
                count_col = 0;
                row++;
            }
        }
    }
    // Gerando a matriz
    return create_matrix(elements, matrix.n_rows, matrix.n_cols * reps);
    
}

// MANIPULAÇÃO DE DIMENSÕES
Matrix transpose(Matrix matrix){ // Corrigida
    Matrix t = matrix;

    t.stride_rows = matrix.stride_cols;
    t.stride_cols = matrix.stride_rows;

    t.n_rows = matrix.n_cols;
    t.n_cols = matrix.n_rows;
    
    return t;

}

Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols){

    // OBS: Em uma matriz comum, não é necessário fazer um malloc para fazer o reshape.
    // Basta manipular seus atributos de linhas, colunas e strides.
    // No entanto, para matrizes obtidas a partir da transposta de uma matriz original
    // e para slices, a função feita manipulando apenas os atributos de linhas, colunas
    // e strides apresentou comportamento inesperado.
    // Com o objetivo de que todas as funções funcionem entre si sem apresentar comportamento
    // anômalo, reshape retornará uma nova matriz.

    int orig_q = N_ELEM;
    int new_q = new_n_rows * new_n_cols;

    if(orig_q == new_q){

        int *elements;
        elements = malloc(sizeof(int) * N_ELEM );

        int read_index = 0, index = 0;

        for (int i = 0; i < matrix.n_rows; i++){
            for (int j = 0; j < matrix.n_cols; j++){
                read_index = i * matrix.stride_rows + j * matrix.stride_cols + matrix.offset;
                index = i * matrix.n_cols + j;

                elements[index] = matrix.data[read_index];
            }
        }

        return create_matrix(elements, new_n_rows, new_n_cols);

    }

    else{
        printf("\033[0;31mValue Error\033[96m: cannot reshape array of size %d into shape (%d,%d)\033[0m\n", orig_q, new_n_rows, new_n_cols);
        return matrix;
    }
}


Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce){ // Corrigida
    if (rs >= 0 && re <= a_matrix.n_rows && cs >= 0 && ce <= a_matrix.n_cols)
    {
        Matrix slc = a_matrix;

        slc.n_rows = re - rs;
        slc.n_cols = ce - cs;
        slc.offset = rs * a_matrix.stride_rows + cs* a_matrix.stride_cols + a_matrix.offset;

        return slc;
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

        int read_m1 = 0, read_m2 = 0, index = 0;

        elements = malloc(sizeof(int) * n_elem);
        // Preenchendo o array unidimensional de saída com base
        // na soma dos elementos de mesmo índice pertencentes à cada matriz
        for (int i = 0; i < matrix_1.n_rows; i++){
            for (int j = 0; j < matrix_1.n_cols; j++){
                read_m1 = i * matrix_1.stride_rows + j * matrix_1.stride_cols + matrix_1.offset;
                read_m2 = i * matrix_2.stride_rows + j * matrix_2.stride_cols + matrix_2.offset;
                index = i * matrix_1.n_cols + j;
                elements[index] = matrix_1.data[read_m1] + matrix_2.data[read_m2];
            }
        }
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

        int read_m1 = 0, read_m2 = 0, index = 0; 
        // Preenchendo o array unidimensional de saída com base
        // na subtração dos elementos de mesmo índice pertencentes à cada matriz
        for (int i = 0; i < matrix_1.n_rows; i++){
            for (int j = 0; j < matrix_1.n_cols; j++){
                read_m1 = i * matrix_1.stride_rows + j * matrix_1.stride_cols + matrix_1.offset;
                read_m2 = i * matrix_2.stride_rows + j * matrix_2.stride_cols + matrix_2.offset;
                index = i * matrix_1.n_cols + j;
                elements[index] = matrix_1.data[read_m1] - matrix_2.data[read_m2];
            }
        }
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
        
        int read_m1 = 0, read_m2 = 0, index = 0; 
        // Preenchendo o array unidimensional de saída com base
        // na divisão dos elementos de mesmo índice pertencentes à cada matriz
        for (int i = 0; i < matrix_1.n_rows; i++){
            for (int j = 0; j < matrix_1.n_cols; j++){
                read_m1 = i * matrix_1.stride_rows + j * matrix_1.stride_cols + matrix_1.offset;
                read_m2 = i * matrix_2.stride_rows + j * matrix_2.stride_cols + matrix_2.offset;
                index = i * matrix_1.n_cols + j;
        /*
        Casos especiais da divisão: 
        1º - denominador 0, resultado 'inf' (usaremos -666 representar),
        2º - numerador e denominador 0, resultado 'nan' (usaremos -777 para representar)
        */
                if(matrix_2.data[read_m2] == 0){
                    if(matrix_1.data[read_m1] == 0){
                        elements[index] = -777;
                        printf("\033[0;33mwarning:   -777 at position [%d, %d] of the matrix symbolizes the result 'nan' found by dividing 0 by 0\033[0m\n", i, j);
                }
                    else{
                        elements[index] = -666;
                        printf("\033[0;33mwarning:   -666 at position [%d, %d] of the matrix symbolizes the result 'inf' found by dividing a number by 0\033[0m\n", i, j);
                }
            }
            else{
                elements[index] = matrix_1.data[read_m1] / matrix_2.data[read_m2];
            }
                
        }
    }
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

        int read_m1 = 0, read_m2 = 0, index = 0;
        // Preenchendo o array unidimensional de saída com base
        // na multiplicação dos elementos de mesmo índice pertencentes à cada matriz
        for (int i = 0; i < matrix_1.n_rows; i++){
            for (int j = 0; j < matrix_1.n_cols; j++){
                read_m1 = i * matrix_1.stride_rows + j * matrix_1.stride_cols + matrix_1.offset;
                read_m2 = i * matrix_2.stride_rows + j * matrix_2.stride_cols + matrix_2.offset;
                index = i * matrix_1.n_cols + j;
                elements[index] = matrix_1.data[read_m1] * matrix_2.data[read_m2];
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

// ACESSANDO ELEMENTOS
int get_element(Matrix matrix, int ri, int ci){ // Corrigida
    if(ri < matrix.n_rows && ci < matrix.n_cols){
        int read_index = ri * matrix.stride_rows + ci *matrix.stride_cols + matrix.offset;
        int element = matrix.data[read_index];

        return element;
    }

    else{
        // Caso os índices de linha e/ou coluna ultrapassem os índices da matriz original,
        // será retornado -999999 para representar o erro 'Index Error'.
        printf("\033[0;31mIndex Error\033[96m: index is out of bounds\033[0m\n");
        return -999999;
    }
}

void put_element(Matrix matrix, int ri, int ci, int elem){ // Corrigida
    if(ri < matrix.n_rows && ci < matrix.n_cols){
        int read_index = ri * matrix.stride_rows + ci * matrix.stride_cols + matrix.offset;
        matrix.data[read_index] = elem;
    }

    else{
        // Caso os índices de linha e/ou coluna ultrapassem os índices da matriz original,
        // será retornado uma mensagem de erro.
        printf("\033[0;31mIndex Error\033[96m: index is out of bounds\033[0m\n");
    }
}

void print_matrix(Matrix matrix){ // Corrigida
    int read_index = 0;
    for (int i = 0; i < matrix.n_rows; i++) {
        putchar('\n');
        for (int j = 0; j< matrix.n_cols; j++){
            read_index = i * matrix.stride_rows + j * matrix.stride_cols + matrix.offset ;
            printf("%d\t", matrix.data[read_index]);
    }
    }
    printf("\n\n");
}

// FUNÇÕES DE AGREGAÇÃO
int min(Matrix matrix){
    int minor = matrix.data[matrix.offset];
    int read_index = 0;

    for(int i = 0; i < matrix.n_rows; i++){
        for (int j = 0; j < matrix.n_cols; j++){
            read_index = i * matrix.stride_rows + j * matrix.stride_cols + matrix.offset;
             if(matrix.data[read_index] < minor){
                minor = matrix.data[read_index];
        }
        }
    }

    return minor;
}

int max(Matrix matrix){
    int major = matrix.data[matrix.offset];
    int read_index = 0;

    for(int i = 0; i < matrix.n_rows; i++){
        for (int j = 0; j < matrix.n_cols; j++){
            read_index = i * matrix.stride_rows + j * matrix.stride_cols + matrix.offset;
             if(matrix.data[read_index] > major){
                major = matrix.data[read_index];
        }
        }
    }
    return major;
}

int argmin(Matrix matrix){
    int minor = min(matrix);
    int read_index = 0, rt_index = 0;

    for(int i = 0; i < matrix.n_rows; i++){
        for (int j = 0; j < matrix.n_cols; j++){
            read_index = i * matrix.stride_rows + j * matrix.stride_cols + matrix.offset;
             if(matrix.data[read_index] == minor){
                rt_index = i * matrix.n_cols + j;
        }
        }
    } // A decisão de retornar o index dessa forma se dá porque, no Numpy original
    // O index retornado é aquele que foi lido como se a matriz fosse gerada apenas pelos
    // elementos lidos. Ou seja, o index é retornado como se o número de elementos da
    // matriz fosse igual ao número de elementos da lista geradora.

    return rt_index;
}

int argmax(Matrix matrix){
    int major = max(matrix);
    int read_index = 0, rt_index = 0;

    for(int i = 0; i < matrix.n_rows; i++){
        for (int j = 0; j < matrix.n_cols; j++){
            read_index = i * matrix.stride_rows + j * matrix.stride_cols + matrix.offset;
             if(matrix.data[read_index] == major){
                rt_index = i * matrix.n_cols + j;
        }
        }
    }
    return rt_index;
}
