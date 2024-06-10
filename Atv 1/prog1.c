/****

LAED2 - ATV1- Prog 1

Aluno: Augusto de Oliveira Soares

Data: 11/08/2023

****/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int ord, i, put, coluna=0, linha=0, impar, parcount=0, flag=0, lap=0;
    int** mat;

    printf("\nDigite a ordem da matriz:");
    scanf("%d", &ord);

    mat = malloc(ord * sizeof(int*));
    for(i=0; i<ord; i++)mat[i] = malloc(ord * sizeof(int));//alocando para matriz

    while(flag == 0){

        if(linha+1 == ord && coluna+1 == ord) flag = 1;
        
        printf("\n\nDigite o elemento da posicao %dx%d: ",linha+1,coluna+1);
        scanf("%d", &put);

        mat[linha][coluna] = put;
        if(put%2 == 0) parcount++;//contador de pares

        if(coluna+1 == ord && linha+1 != ord){
            coluna = 0;
            linha++;
            lap=1;
            
        }//lap é uma variavel suporte para não somar +1 em coluna quando acabar a linha.

        if(lap==0)coluna++;
        else lap=0;

    }
    impar = ord*ord-parcount;//impares = total - pares.
    printf("\nnumero de pares: %d", parcount);
    printf("\nnumero de impares: %d", impar);

    return 0;
}