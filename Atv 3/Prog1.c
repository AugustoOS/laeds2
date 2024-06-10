#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura de um nó da árvore SBB
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int nivel;  // Indica se o nó é uma thread (1) ou não (0)
} Node;

// Função para criar um novo nó da árvore SBB
Node *criarNo(int chave) {
    Node *novoNo = (Node *)malloc(sizeof(Node));
    novoNo->key = chave;
    novoNo->left = novoNo->right = NULL;
    novoNo->nivel = 0;
    return novoNo;
}

// Função para realizar a pesquisa em uma árvore SBB
int pesquisaSBB(Node *raiz, int alvo, int *comparacoes) {
    Node *atual = raiz;
    while (atual) {
        (*comparacoes)++;
        if (atual->key == alvo) {
            return 1; // Elemento encontrado
        } else if (atual->key < alvo) {
            atual = atual->right;
        } else {
            if (atual->nivel) {
                break;
            }
            atual = atual->left;
        }
    }
    return 0; // Elemento não encontrado
}

// Função para criar uma árvore SBB com elementos ordenados
Node *criarSBB(int *array, int esquerda, int direita) {
    if (esquerda > direita) {
        return NULL;
    }

    int meio = (esquerda + direita) / 2;
    Node *raiz = criarNo(array[meio]);

    raiz->left = criarSBB(array, esquerda, meio - 1);
    raiz->right = criarSBB(array, meio + 1, direita);

    // Configura as threads para os nós da folha direita
    if (raiz->right == NULL) {
        raiz->nivel = 1;
        raiz->right = raiz->left;
        raiz->left = NULL;
    }

    return raiz;
}

int main() {
    int n;
    for (n = 10000; n <= 100000; n += 10000) {
        int *array = (int *)malloc(n * sizeof(int));
        int i, comparacoes = 0;
        clock_t inicio, fim;

        // Preenche o array ordenado com elementos de 1 a n
        for (i = 0; i < n; i++) {
            array[i] = i + 1;
        }

        // Cria a árvore SBB
        Node *raiz = criarSBB(array, 0, n - 1);

        // Realiza a pesquisa por um elemento que não existe na árvore
        int alvo = n + 1;
        inicio = clock();
        int resultado = pesquisaSBB(raiz, alvo, &comparacoes);
        fim = clock();

        // Calcula o tempo gasto na pesquisa
        double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

        // Imprime os resultados
        printf("Numero de elementos: %d\n", n);
        printf("Numero de comparacoes: %d\n", comparacoes);
        printf("Tempo gasto na pesquisa: %f segundos\n", tempo_gasto);
        printf("\n---------------\n");

        free(array);
    }

    return 0;
}