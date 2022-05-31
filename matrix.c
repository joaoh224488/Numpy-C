/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define default_stride_cols 1 // Pulará um por padrão
#define default_offset 0      // Consideraremos o array do início por padrão


// CRIAÇÃO DE MATRIZES
Matrix create_matrix(int *data, int n_rows, int n_cols){
    // Inicialização da matriz
    Matrix mat;

    // Inicializando o 'construtor' da struct
    mat.data = data;
    mat.n_rows = n_rows;
    mat.n_cols = n_cols;
    mat.stride_rows = n_cols;
    mat.stride_cols = default_stride_cols;
    mat.offset = default_offset;

    return mat;
}

Matrix zeros_matrix(int n_rows, int n_cols){

    return full_matrix(n_rows, n_cols, 0);
} 

Matrix full_matrix(int n_rows, int n_cols, int value){
    // Inicialização da matriz
    Matrix full_mat;

    // Criando a lista de dados
    int *list_values;
    int n_elem = n_cols * n_rows;
    list_values = malloc(sizeof(int) * n_elem);

    for (int i = 0; i < n_elem; i++){
        list_values[i] = value;
    }

    // Gerando a matriz
    full_mat = create_matrix(list_values, n_rows, n_cols);

    return full_mat;
}

Matrix i_matrix (int n){
    // Inicialização da matriz
    Matrix i_mat;

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
    i_mat = create_matrix(list_values, n, n);

    return i_mat;
}

Matrix tile_matrix(Matrix matrix, int reps){
    // Inicialização da matriz
    Matrix tile;

    int *elements;
    int n_elem = matrix.n_rows * matrix.n_cols;
    elements = malloc(sizeof(int) * n_elem * reps);

    int j = 0;
    int k = 0;
    int line = 1;
    for(int i = 0; i < n_elem * reps; i++){
        elements[i] = matrix.data[j];
        j++;
        if(j % matrix.n_cols == 0){
            j = k;
        }
        if(line % (matrix.n_rows+1) == 0){
            k += matrix.n_cols;
            j = k;
        }
        line++;

    }

    tile = create_matrix(elements, matrix.n_rows, matrix.n_cols*reps);

    return tile;
}

/*Matrix tile_matrix(Matrix matrix, int reps){
    Matrix tile;

    int *elements;
    int n_elem = matrix.n_rows * matrix.n_cols;
    elements = malloc(sizeof(int) * n_elem*reps);

    int j = 0;
    int k = 0;
    int line = 1;
    for(int i = 0; i < n_elem * reps; i++){
        elements[i] = matrix.data[j];
        j++;
        if(j % matrix.n_cols == 0){
            j = k;
        }
        if(i+1 == (n_elem) * line){
            k += matrix.n_cols;
            j = k;
            line+=1;
        }
    }

    tile = create_matrix(elements, matrix.n_rows, matrix.n_cols*reps);

    return tile;
}*/

// MANIPULAÇÃO DE DIMENSÕES
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

    if(orig_q == new_q){
        Matrix re_mat = matrix;

        re_mat.n_rows = new_n_rows;
        re_mat.n_cols = new_n_cols;
        re_mat.stride_rows = new_n_cols;

        return re_mat;
    }
}

// OPERAÇÕES ARITMÉTICAS
Matrix add(Matrix matrix_1, Matrix matrix_2){
    // Verificando se matrizes têm as mesmas dimensões
    if(matrix_1.n_rows == matrix_2.n_rows && matrix_1.n_cols == matrix_2.n_cols){
        // Inicialização da matriz
        Matrix sum;
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
        sum = create_matrix(elements, matrix_1.n_rows, matrix_1.n_cols);

        return sum;
    }
}

Matrix sub(Matrix matrix_1, Matrix matrix_2){
    // Verificando se matrizes têm as mesmas dimensões
    if(matrix_1.n_rows == matrix_2.n_rows && matrix_1.n_cols == matrix_2.n_cols){
        // Inicialização da matriz
        Matrix subtraction;
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
        subtraction = create_matrix(elements, matrix_1.n_rows, matrix_1.n_cols);

        return subtraction;
    }
}

Matrix division(Matrix matrix_1, Matrix matrix_2){
    // Verificando se matrizes têm as mesmas dimensões
    if(matrix_1.n_rows == matrix_2.n_rows && matrix_1.n_cols == matrix_2.n_cols){
        // Inicialização da matriz
        Matrix div;
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
        div = create_matrix(elements, matrix_1.n_rows, matrix_1.n_cols);

        return div;
    }
}

Matrix mul(Matrix matrix_1, Matrix matrix_2){
    // Verificando se matrizes têm as mesmas dimensões
    if(matrix_1.n_rows == matrix_2.n_rows && matrix_1.n_cols == matrix_2.n_cols){
        // Inicialização da matriz
        Matrix multiplication;
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
        multiplication = create_matrix(elements, matrix_1.n_rows, matrix_1.n_cols);

        return multiplication;
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

// FUNÇÕES DE AGREGAÇÃO
int min(Matrix matrix){
    int minor = matrix.data[0];

    for(int i = 1; i < matrix.n_rows * matrix.n_cols; i++){
        if(matrix.data[i] < minor){
            minor = matrix.data[i];
        }
    }

    return minor;
}

int max(Matrix matrix){
    int major = matrix.data[0];

    for(int i = 1; i < matrix.n_rows * matrix.n_cols; i++){
        if(matrix.data[i] > major){
            major = matrix.data[i];
        }
    }

    return major;
}

int argmin(Matrix matrix){
    int minor_index = 0;

    for(int i = 0; i < matrix.n_rows * matrix.n_cols; i++){
        if(matrix.data[i] == min(matrix)){
            minor_index = i;
        }
    }

    return minor_index;
}

int argmax(Matrix matrix){
    int major_index = 0;

    for(int i = 0; i < matrix.n_rows * matrix.n_cols; i++){
        if(matrix.data[i] == max(matrix)){
            major_index = i;
        }
    }

    return major_index;
}