/****

LAED2 - ATV1- Prog 5

Aluno: Augusto de Oliveira Soares

Data: 11/08/2023

****/

#include <stdio.h>
#include <stdlib.h>

void quicksort(int arr[],int min,int max);
int particao(int arr[], int min, int max);

int main(){
    int num, i;

    printf("Digite o numero de elementos do vetor a ser ordenado: ");
    scanf("%d", &num);

    int *arr = malloc(num * sizeof(int));//aloca o vetor no tamanho de num

    for(i=0;i<num;i++){
        printf("Digite o elemento %d: ",i+1);
        scanf("%d", &arr[i]);
    }//registra no vetor
    
    quicksort(arr,0,num-1);//chama a funcao quicksort
    
    printf("\nVetor ordenado:\n\n{");
    for(i=0;i<num;i++){
        if(i == num-1) printf("%d}",arr[i]);
        else printf("%d,",arr[i]);
    }//printa o vetor apos ser tratado
    
    return 0;
}

void quicksort(int arr[],int min,int max){
    int pivo;
    if(min < max){//se o vetor tem tamanho maior que 1
        pivo = particao(arr,min,max);
        quicksort(arr,min,pivo-1);//para a metade dos menores que o pivo
        quicksort(arr,pivo+1,max);//para a metade dos maiores que o pivo
    }

}

int particao(int arr[], int min, int max){

    int i, indice = min, pivo = arr[max], aux;
    
    for(i = min;i<max;i++){
            if(arr[i]<=pivo){
                //troca o elemento do vetor na posicao i com a da posicao indice
                aux = arr[i];
                arr[i] = arr[indice];
                arr[indice] = aux;

                indice++;
            }
    }
    //apos organizado em funcao do pivo, coloca o pivo no meio das divisoes
    aux = arr[indice];
    arr[indice] = arr[max];
    arr[max] = aux;

    return indice;
}

