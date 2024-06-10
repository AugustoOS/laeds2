#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura do nó da árvore binária de busca
struct NoArvore {
    int dado;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
};

// Função para criar um novo nó da árvore
struct NoArvore *novoNo(int dado) {
    struct NoArvore *no = (struct NoArvore *)malloc(sizeof(struct NoArvore));
    no->dado = dado;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// Função para inserir um nó na árvore
struct NoArvore *inserir(struct NoArvore *raiz, int dado) {
    if (raiz == NULL) {
        return novoNo(dado); // Cria um novo nó com o dado fornecido
    }

    // Se o dado é menor que o dado da raiz, insere na subárvore esquerda
    if (dado < raiz->dado) {
        raiz->esquerda = inserir(raiz->esquerda, dado);
    }
    // Se o dado é maior que o dado da raiz, insere na subárvore direita
    else if (dado > raiz->dado) {
        raiz->direita = inserir(raiz->direita, dado);
    }

    return raiz; // Retorna a raiz da árvore atualizada
}

// Função para realizar uma pesquisa na árvore
int buscar(struct NoArvore *raiz, int chave, int *comparacoes) {
    if (raiz == NULL) {
        return 0; // Não encontrou o elemento, retorna 0
    }

    (*comparacoes)++; // Conta a comparação realizada
    
    // Se a chave é igual ao dado do nó atual, encontrou o elemento
    if (chave == raiz->dado) {
        return 1;
    }
    // Se a chave é menor que o dado do nó atual, busca na subárvore esquerda
    else if (chave < raiz->dado) {
        return buscar(raiz->esquerda, chave, comparacoes);
    }
    // Se a chave é maior que o dado do nó atual, busca na subárvore direita
    else {
        return buscar(raiz->direita, chave, comparacoes);
    }
}

int main() {
    srand(time(NULL));

    int inicio_n = 1000;
    int fim_n = 9000;
    int passo = 1000;

    for (int n = inicio_n; n <= fim_n; n += passo) {
        struct NoArvore *raiz = NULL;

        // Inserção de elementos aleatórios na árvore
        for (int i = 0; i < n; i++) {
            int elemento = rand() % (n * 10); // Gera elementos aleatórios
            raiz = inserir(raiz, elemento);
        }

        int chave = n + rand() % passo; // Elemento não existente na árvore
        int comparacoes = 0;
        
        // Realização da pesquisa e medição de tempo
        clock_t tempo_inicio = clock();
        int encontrado = buscar(raiz, chave, &comparacoes);
        sleep(1);
        clock_t tempo_fim = clock();
        double tempo_decorrido = (double)(1000*(tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;

        printf("Para n = %d:\n", n);
        printf("Elemento %d %sachado. Comparacoes: %d. Tempo: %.6f milisegundos.\n\n",
               chave, encontrado ? "" : "nao ", comparacoes, tempo_decorrido);

        // Liberar a memória da árvore após cada iteração
        // (pode ser feito de forma mais eficiente em uma aplicação real)
        free(raiz);
    }

    return 0;
}