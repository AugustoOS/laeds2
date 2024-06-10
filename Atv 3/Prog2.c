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

// Função para criar uma árvore SBB com elementos aleatórios
Node *inserirAleatoriamente(Node *raiz, int chave) {
    if (raiz == NULL) {
        return criarNo(chave);
    }

    // Probabilidade de inserção à esquerda ou direita
    int probabilidade = rand() % (raiz->key + 1);

    if (probabilidade < chave) {
        raiz->left = inserirAleatoriamente(raiz->left, chave);
    } else {
        raiz->right = inserirAleatoriamente(raiz->right, chave);
    }

    return raiz;
}

int main() {
    srand(time(NULL));  // Inicializa a semente para números aleatórios

    for (int n = 10000; n <= 100000; n += 10000) {
        int comparacoes = 0;
        clock_t inicio, fim;

        for (int i = 0; i < 10; i++) {
            // Cria uma árvore SBB com elementos aleatórios
            Node *raiz = NULL;
            for (int j = 0; j < n; j++) {
                raiz = inserirAleatoriamente(raiz, rand() % (n * 10)); // Números aleatórios de 0 a n*10
            }

            // Realiza a pesquisa por um elemento que não existe na árvore
            int alvo = n * 10 + 1; // Um elemento que não existe na árvore
            
            inicio = clock();
            int resultado = pesquisaSBB(raiz, alvo, &comparacoes);
            sleep(1);
            fim = clock();
            

            // Libera a memória da árvore
            liberarArvore(raiz);
        }

        double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

        // Imprime os resultados médios
        printf("Numero de elementos: %d\n", n);
        printf("Numero de comparacoes: %d\n", comparacoes);
        printf("Tempo gasto na pesquisa: %f segundos\n", tempo_gasto);
        printf("\n---------------\n");
    }

    return 0;
}

// Função para liberar a memória de uma árvore
void liberarArvore(Node *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->left);
        liberarArvore(raiz->right);
        free(raiz);
    }
}
