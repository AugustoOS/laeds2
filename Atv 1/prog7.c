/****

LAED2 - ATV1- Prog 7

Aluno: Augusto de Oliveira Soares

Data: 11/08/2023

****/

#include <stdio.h>

// Função de busca binária
int buscaBinaria(int vetor[], int tamanho, int alvo) {
    int esquerda = 0;
    int direita = tamanho - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        // Verifica se o alvo está no meio
        if (vetor[meio] == alvo) return meio;

        // Se o alvo for maior, descarta a metade esquerda
        if (vetor[meio] < alvo) esquerda = meio + 1;
        // Se o alvo for menor, descarta a metade direita
        else direita = meio - 1;
    }

    // Retorna -1 se o alvo não estiver no vetor
    return -1;
}

int main() {
    int vetor[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    int i,alvo, tamanho, resultado;

    tamanho = sizeof(vetor) / sizeof(int);

    printf("\nDado o seguninte vetor ordenado\n\n{");
    for(i=0;i<tamanho;i++){
        if(i == tamanho-1) printf("%d}",vetor[i]);
        else printf("%d,",vetor[i]);
    }

    printf("\n\nDigite o elemento a ser buscado: ");
    scanf("%d", &alvo);
    
    resultado = buscaBinaria(vetor, tamanho, alvo);

    if (resultado != -1){
        printf("O elemento %d foi encontrado na posicao %d.\n", alvo, resultado+1);
        printf("P.S.: O primeiro elemento esta convencionado com a posicao 1, entao os outros elementos carregam essa referencia.");
    }
    else printf("O elemento %d não foi encontrado no vetor.\n", alvo);

    return 0;
}