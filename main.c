/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#include <stdio.h>
#include "matrix.h"

int main(){
    int T[12]   =      {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2};
    int a[4]    =      {11, 1, -8, 3};
    int b[9]    =      {-13, -1, 17, 5, 16, 0, 11, -2, 17};
    int c[16]   =      {5, 0, 3, 2, 5, -3, -4, -14, -1, -12, 3, 19, -5, 5, 0, 7};

    int d[4]    =      {-4, 8, 0, -5};
    int e[9]    =      {3, 5, 1, 2, -5, 16, 2, -15, 5};
    int f[16]   =      {24, -1, 0, -2, 8, 3, 20, -3, 21, 0, 11, 1, -12, -2, 8, 0};

    int g[4]    =      {-7, -3, 15, 0};
    int h[6]    =      {1, 4, 0, -1, 2, -2};
    int i[10]   =      {-5, 0, 4, -4, -13, 1, -2, -1, -2, 2};
    int j[15]   =      {12, -2, 18, 0, 0, -2, 10, -3, 17, 2, 9, 2, 16, 5, 19};     

    Matrix m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20;

    m14 = create_matrix(T, 3, 4);
    m1 = create_matrix(a,2,2), m2 = create_matrix(d,2,2);
    m3 = create_matrix(b,3,3), m4 = create_matrix(e,3,3);
    m5 = create_matrix(c,4,4), m6 = create_matrix(f,4,4);

    printf("Exibindo as 6 matrizes simétricas:\n\n");

    print_matrix(m1);
    print_matrix(m2);
    print_matrix(m3);
    print_matrix(m4);
    print_matrix(m5);
    print_matrix(m6);

    printf("Soma de matrizes:\n");
    m7 = add(m3, m4);
    print_matrix(m7);

    printf("Subtração de matrizes:\n");
    m8 = sub(m3, m4);
    print_matrix(m8);

    printf("Multiplicação de matrizes:\n");
    m9 = mul(m3, m4);
    print_matrix(m9);

    printf("Divisão de matrizes:\n");
    m10 = division(m3, m4);
    print_matrix(m10);

    m11 = zeros_matrix(6,4);
    m12 = full_matrix(5,2,9);
    m13 = i_matrix(7);

    print_matrix(m11), print_matrix(m12), print_matrix(m13);

    print_matrix(m14);
    m15 = reshape(m14, 2, 6);
    print_matrix(m15);
    //para corrigir
    print_matrix(transpose(m14));

    int data[] = {1, 2, 3, 4};

    Matrix ex = create_matrix(data, 2, 2);

    print_matrix(ex);

    Matrix sliced = slice(m13, 1, 3, 0, 4);

    print_matrix(sliced);

    return 0;
}