/****

LAED2 - ATV1- Prog 4

Aluno: Augusto de Oliveira Soares

Data: 11/08/2023

****/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int i,j=0,k;
    int **mat;

    mat = malloc(3 * sizeof(int*));
    for(i=0; i<3; i++) mat[i]= malloc(6*sizeof(int));//alocando para matriz

    mat[0][0] = 40000;
    mat[1][0] = 100000;
    mat[2][0] = 80000;//populações em 2023
    
    for(k=0; k<3;k++){
        for(i=0;i<7;i++){//repetir ate 2028
            printf("%d ", mat[j][i]);
            mat[j][i+1] = mat[j][i]*1.02;
        }
        j++;
        printf("\n");
    }


    return 0;

}