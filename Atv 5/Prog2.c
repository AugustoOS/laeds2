#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Função para realizar o heapsort e contar comparações
int heapsort(int vet[], int n)
{
    int comp = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        comp += ajustarHeap(vet, n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        comp += trocar(&vet[0], &vet[i]);
        comp += ajustarHeap(vet, i, 0);
    }
    return comp;
}
// Função para ajustar o heap máximo
int ajustarHeap(int vet[], int n, int i)
{
    int comp = 0;
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    if (esq < n && vet[esq] > vet[maior])
    {
        maior = esq;
    }
    if (dir < n && vet[dir] > vet[maior])
    {
        maior = dir;
    }
    if (maior != i)
    {
        comp += trocar(&vet[i], &vet[maior]);
        comp += ajustarHeap(vet, n, maior);
    }
    return comp;
}
// Função para trocar dois elementos de posição
int trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return 1; // Contabiliza uma comparação
}
int main()
{
    srand(time(NULL));
    int i, j;
    // Loop para gerar 10 vetores
    for (int n = 10000; n <= 100000; n += 10000)
    {
        int *vet = (int *)malloc(n * sizeof(int));
        // Preenche o vetor com números em ordem crescente
        for (i = n, j = 0; i > 0; i--)
        {
            vet[j] = i;
            j++;
        }
        // Embaralha o vetor para garantir que esteja desordenado
        /*for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        trocar(&vet[i], &vet[j]);
        }*/
        // Realiza o heapsort e conta as comparações
        int comp = heapsort(vet, n);
        printf("Tamanho do vetor: %d, Comparacoes: %d\n", n, comp);
        free(vet);
    }
    return 0;
}
Output : Tamanho do vet