/****

LAED2 - ATV1- Prog 2

Aluno: Augusto de Oliveira Soares

Data: 11/08/2023

****/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int ord1, ord2, i,j, put, coluna, linha, flag, lap=0;
    int **mat1,**mat2, **mat3;

    printf("Informe a ordem da primeira matriz: ");
    scanf("%d", &ord1);
    mat1 = malloc(ord1 * sizeof(int*));
    for(i=0; i<ord1; i++)mat1[i] = malloc(ord1 * sizeof(int));//alocando para matriz1

    printf("Informe a ordem da primeira matriz: ");
    scanf("%d", &ord2);
    mat2 = malloc(ord2 * sizeof(int*));
    for(i=0; i<ord2; i++)mat2[i] = malloc(ord2 * sizeof(int));//alocando para matriz2

    if(ord1==ord2){

        mat3 = malloc(ord1 * sizeof(int*));
        for(i=0; i<ord1; i++)mat3[i] = malloc(ord1 * sizeof(int));//alocando para matriz resultado

        for(i=0;i<2;i++){

            coluna = 0, linha = 0,flag = 0;
            printf("\n\n\t--MATRIZ %d--\n",i+1);

            while(flag == 0){

                if(linha+1 == ord1 && coluna+1 == ord1) flag = 1;
                
                printf("\n\nDigite o elemento da posicao %dx%d: ",linha+1,coluna+1);
                scanf("%d", &put);

                if(i==0) mat1[linha][coluna] = put;
                else{ 
                    mat2[linha][coluna] = put;
                    mat3[linha][coluna] = mat2[linha][coluna]+mat1[linha][coluna];
                }

                if(coluna+1 == ord1 && linha+1 != ord1){
                    coluna = 0;
                    linha++;
                    lap=1;
                }//lap é uma variavel suporte para não somar +1 em coluna quando acabar a linha.

                if(lap==0)coluna++;
                else lap=0;

            }
        }

        printf("\n\n--MATRIZ RESULTANTE--\n");
           
        for(i=0;i<ord1;i++){
            for(j=0;j<ord1;j++){
            printf("%d ",mat3[i][j]);
            }
            printf("\n");
        }

    }else{

        printf("\nAs duas matrizes devem ter a mesma ordem para serem somados.");

    }
    return 0;
}