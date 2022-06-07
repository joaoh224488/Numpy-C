/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#include <stdio.h>
#include "matrix.h"

int main(){
    // Matriz de zeros:
    printf("\033[96mCriação de matrizes:    \033[0m\n\n");
    printf("Matriz 3x5 de zeros:\n");
    Matrix m_zeros = zeros_matrix(3, 5); 
    print_matrix(m_zeros);

    // Matriz preenchida com um número qualquer:

    printf("Matriz 4x4 preenchida por números 7:\n");
    Matrix full_of_seven = full_matrix(4, 4, 7); 
    print_matrix(full_of_seven);

    //Matriz identidade:
    printf("Identidade de ordem 5:\n");
    Matrix eye = i_matrix(5); 
    print_matrix(eye);

    // Criando uma matriz com dados quaisquer:
    int data[] = {1, -5, 2, 9};
    printf("Matriz qualquer:    \n");
    Matrix a_matrix = create_matrix(data, 2, 2);
    print_matrix(a_matrix);

    // Criando uma matriz com dados repetidos de a_matrix:

    printf("Tile matrix usando os dados da matriz anterior:\n");
    Matrix til_mat = tile_matrix(a_matrix, 3);
    print_matrix(til_mat);

    printf("\033[96m-----------------------------------------------------\033[0m\n\n");

    printf("\033[96mAcessando elementos:    \033[0m\n\n");
    int elemento = get_element(a_matrix, 0, 1);
    printf("O elemento da linha 0 e coluna 1 da matriz gerada é: %d.\n", elemento);

    // Substituindo -5 por 10 na matriz:
    put_element(a_matrix, 0, 1, 10);
    print_matrix(a_matrix);
    printf("\033[96m-----------------------------------------------------\033[0m\n\n");

    printf("\033[96mFunções para manipulação de dimensões:    \033[0m\n\n");
    // Criando uma nova matriz:
    int other_data[] = {1, 7, 8, 9, 0, 2};
    printf("Outra matriz qualquer:    \n");
    Matrix another = create_matrix(other_data, 3, 2);
    print_matrix(another);

    // Fazendo a transposta da matriz:
    printf("Transposta da matriz:    \n");
    Matrix t = transpose(another);
    print_matrix(t);

    // Fazendo o reshape da matriz:
    printf("Matriz com as dimensões 2x3:    \n");
    Matrix shaped = reshape(another, 2, 3);
    print_matrix(shaped);

    // Fazendo um slice da matriz shaped
    printf("Slice da matriz:    \n");

    Matrix cut = slice(shaped, 0, 2, 1, 3);
    print_matrix(cut);

    printf("\033[96m-----------------------------------------------------\033[0m\n\n");

    // Retorno das funções de agregação a partir da matriz cut:
    printf("\033[96mFunções de agregação:    \033[0m\n\n");

    printf("O elemento mínimo da matriz gerada pelo slice é:    %d\n", min(cut));
    printf("O índice na lista geradora desse elemento é:    %d\n", argmin(cut));
    printf("O elemento máximo da matriz gerada pelo slice é:    %d\n", max(cut));
    printf("O índice desse na lista geradora elemento é:    %d\n\n", argmax(cut));

    printf("\033[96m-----------------------------------------------------\033[0m\n\n");

    // Funções que realizam operações aritméticas:
    printf("\033[96mOperações aritméticas:    \033[0m\n\n");
    int data_m1[] = {2, 4, 6, 8};
    int data_m2[] = {1, 2, 3, 4};

    printf("Primeira matriz:    ");
    Matrix m1 = create_matrix(data_m1, 2, 2);
    print_matrix(m1);
    printf("Segunda matriz:    ");
    Matrix m2 = create_matrix(data_m2, 2, 2);
    print_matrix(m2);

    printf("Soma das matrizes:\n");
    Matrix sum = add(m1, m2);
    print_matrix(sum); 

    printf("Subtração das matrizes:\n");
    Matrix minus = sub(m1, m2);
    print_matrix(minus);

    printf("Multiplicação das matrizes:\n");
    Matrix multiplication = mul(m1, m2);
    print_matrix(multiplication);  

    printf("Divisão das matrizes:\n");
    Matrix div = division(m1, m2);
    print_matrix(div);  
    printf("\033[96m-----------------------------------------------------\033[0m\n\n");
    
    return 0;

}