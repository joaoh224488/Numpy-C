/*
    João Henrique -> 20210026705 
    Max Barbosa   -> 20210067083 
*/


#include <stdio.h>
#include "matrix.h"

int main(){
    int data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12};

    Matrix m1 = create_matrix(data, 3, 4);

    print_matrix(m1);
    
    return 0;
}