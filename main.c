#include <stdio.h>
#include "matrix.h"

int main(){
    printf("Bateria de testes:\n«-------------------------------------------------»\n");

    // Criação de matrizes
    int a[10] = {1,2,3,4,5,6,7,8,9,0};

    Matrix m1 =  create_matrix(a,5,2);
    Matrix zeros = zeros_matrix(5,5);
    Matrix full = full_matrix(3,3,7);
    Matrix eye = i_matrix(4);
    Matrix tile_m1 = tile_matrix(m1, 5);

    printf("Matriz 5x2:\n");
    print_matrix(m1);
    printf("Matriz 5x5 de zeros:\n");
    print_matrix(zeros);
    printf("Matriz 3x3 de 7s:\n");
    print_matrix(full);
    printf("Matriz identidade de ordem 4:\n");
    print_matrix(eye);
    printf("Repetindo 5 vezes a matriz 5x2 inicial:\n");
    print_matrix(tile_m1);

    // ------------------------------------------------

    // Manipulando dimensões
    int b[12] = {-2, 4, 2, 1, 0, -9, 10, 3, 5, 6, 8, 7};
    Matrix m2 = create_matrix(b,4,3);
    Matrix transp_m2 = transpose(m2);
    Matrix rshape_m2 = reshape(m2,3,4);
    Matrix slc_m2 = slice(rshape_m2, 0, 3, 0, 3);
    
    printf("Matriz 'm2' 4x3 qualquer:\n");
    print_matrix(m2);
    printf("Matriz transposta de m2 (transp_m2):\n");
    print_matrix(transp_m2);
    printf("Reshape de m2 sendo agora 4x3 (rshape_m2):\n");
    print_matrix(rshape_m2);
    printf("Fatiamento [0:3, 0:3] de 'rshape_m2' (slc_m2):\n");
    print_matrix(slc_m2);

    // ------------------------------------------------

    int limbo[9] = {-2,4,2,0,-9,10,5,6,8};
    Matrix teste =  create_matrix(limbo,3,3);

    printf("Matriz 'teste' 3x3:\n");
    print_matrix(teste);

    // Funções de agregação

    // A saída bate com os resultados de 'slc_m2', já que se trata da mesma matriz, sendo a segunda
    // um fatiamento de outra.
    printf("Valores mínimo e máximo de 'teste':\n");

    printf("min:    %d\n", min(teste));
    printf("argmin: %d\n", argmin(teste));
    printf("max:    %d\n", max(teste));
    printf("argmax  %d\n", argmax(teste));

    // ------------------------------------------------

    // Operações aritméticas
    int numbers[3] = {0, -1, 5};
    Matrix op = create_matrix(numbers, 1, 3);

    print_matrix(op);
    print_matrix(slice(slc_m2, 1, 2, 0, 3));

    printf("sum:");
    print_matrix(add(op, slice(slc_m2, 1, 2, 0, 3)));
    printf("sub:");
    print_matrix(sub(op, slice(slc_m2, 1, 2, 0, 3)));
    printf("mul:");
    print_matrix(mul(op, slice(slc_m2, 1, 2, 0, 3)));
    printf("div:");
    print_matrix(division(op, slice(slc_m2, 1, 2, 0, 3)));

    return 0;
}