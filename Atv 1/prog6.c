/****

LAED2 - ATV1- Prog 6

Aluno: Augusto de Oliveira Soares

Data: 11/08/2023

****/

#include <stdio.h>
#include <stdlib.h>

void mergesort(int arr[], int left, int right);
void merge(int arr[], int left, int middle, int right);

int main(){

    int num, i;

    printf("Digite o numero de elementos do vetor a ser ordenado: ");
    scanf("%d", &num);

    int *arr = malloc(num * sizeof(int));//aloca o vetor no tamanho de num

    for(i=0;i<num;i++){
        printf("Digite o elemento %d: ",i+1);
        scanf("%d", &arr[i]);
    }//registra no vetor
    
    mergesort(arr,0,num-1);

    printf("\nVetor ordenado:\n\n{");
    for(i=0;i<num;i++){
        if(i == num-1) printf("%d}",arr[i]);
        else printf("%d,",arr[i]);
    }//printa o vetor apos ser tratado

    return 0;
}

void mergesort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Ordena as duas metades
        mergesort(arr, left, middle);
        mergesort(arr, middle + 1, right);

        // Combina as duas metades ordenadas
        merge(arr, left, middle, right);
    }
}

void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Cria subvetores temporários
    int L[n1], R[n2];

    // Copia os dados para as subvetores temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    // Combina os subvetores de volta em arr[l..r]
    i=0,j=0,k= left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}