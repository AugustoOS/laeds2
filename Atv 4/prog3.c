#include <stdio.h>
#include <stdlib.h>

int comparacoes;

// Defina a ordem da árvore B
#define ORDER 4

// Defina a estrutura de nó da árvore B
struct TreeNode {
    int chaves[2 * ORDER - 1];
    struct TreeNode *filhos[2 * ORDER];
    int n_chaves;
    int folha;
};

// Função para criar um novo nó da árvore B
struct TreeNode *criarNo() {
    struct TreeNode *novoNo = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    novoNo->n_chaves = 0;
    novoNo->folha = 1;
    for (int i = 0; i < 2 * ORDER; i++) {
        novoNo->chaves[i] = 0;
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

// Função para inserir uma chave em uma árvore B
void inserirChave(struct TreeNode *raiz, int chave) {
    // Verifique se o nó raiz está cheio
    if (raiz->n_chaves == 2 * ORDER - 1) {
        // Crie um novo nó e defina-o como a nova raiz
        struct TreeNode *novoNo = criarNo();
        novoNo->folha = 0;
        novoNo->filhos[0] = raiz;
        dividirNo(novoNo, 0, raiz); // Divide o nó raiz

        // Atualiza a raiz da árvore
        raiz = novoNo;
    }

    // Insira a chave no nó
    inserirNoNaoCheio(raiz, chave);
}

// Função para inserir uma chave em um nó que não está cheio
void inserirNoNaoCheio(struct TreeNode *no, int chave) {
    int i = no->n_chaves - 1;

    if (no->folha) {
        // Move todas as chaves maiores que a chave a ser inserida para a direita
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }

        // Insere a chave na posição correta
        no->chaves[i + 1] = chave;
        no->n_chaves++;
    } else {
        // Encontra o filho apropriado para a chave
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;

        // Verifica se o filho está cheio
        if (no->filhos[i]->n_chaves == 2 * ORDER - 1) {
            dividirNo(no, i, no->filhos[i]);

            // Decide qual dos dois filhos recentemente criados deve ser o filho apropriado para a inserção
            if (chave > no->chaves[i]) {
                i++;
            }
        }

        // Insere a chave no filho apropriado
        inserirNoNaoCheio(no->filhos[i], chave);
    }
}

// Função para dividir um nó cheio em dois
void dividirNo(struct TreeNode *pai, int indice, struct TreeNode *filho) {
    // Crie um novo nó para armazenar as chaves maiores
    struct TreeNode *novoFilho = criarNo();
    novoFilho->folha = filho->folha;
    novoFilho->n_chaves = ORDER - 1;

    // Copie as chaves maiores para o novo nó
    for (int i = 0; i < ORDER - 1; i++) {
        novoFilho->chaves[i] = filho->chaves[i + ORDER];
    }

    // Se o filho não é uma folha, copie também os filhos correspondentes
    if (!filho->folha) {
        for (int i = 0; i < ORDER; i++) {
            novoFilho->filhos[i] = filho->filhos[i + ORDER];
        }
    }

    // Reduza o número de chaves no filho original
    filho->n_chaves = ORDER - 1;

    // Abra espaço para o novo filho no pai
    for (int i = pai->n_chaves; i > indice; i--) {
        pai->chaves[i] = pai->chaves[i - 1];
        pai->filhos[i + 1] = pai->filhos[i];
    }

    // Insira o novo filho no pai
    pai->chaves[indice] = filho->chaves[ORDER - 1];
    pai->filhos[indice + 1] = novoFilho;
    pai->n_chaves++;
}

// Função para buscar uma chave em uma árvore B e contar as comparações
int buscarChave(struct TreeNode *raiz, int chave) {
    comparacoes = 0;
    
    while (raiz != NULL) {
        int i = 0;
        while (i < raiz->n_chaves && chave > raiz->chaves[i]) {
            i++;
            comparacoes++;
        }

        if (i < raiz->n_chaves && chave == raiz->chaves[i]) {
            comparacoes++;
            return 1; // A chave foi encontrada
        }

        if (raiz->folha) {
            comparacoes++;
            return 0; // A chave não foi encontrada
        } else {
            comparacoes++;
            raiz = raiz->filhos[i]; // Continue a busca nos filhos
        }
    }

    return 0; // A chave não foi encontrada
}

// Função para preencher uma árvore B com números ordenados
void preencherArvore(struct TreeNode *raiz, int inicio, int fim) {
    for (int i = inicio; i <= fim; i++) {
        inserirChave(raiz, i);
    }
}

int main() {
    // Criar as árvores B com diferentes tamanhos
    for (int n = 10000; n <= 100000; n += 10000) {
        struct TreeNode *arvoreB = criarNo();
        preencherArvore(arvoreB, 1, n); // Preencha com números de 1 a n

        int chave = n + 1; // Chave que não existe na árvore
        int encontrado = buscarChave(arvoreB, chave);

        if (encontrado) {
            printf("Chave %d encontrada na arvore B de tamanho %d com %d comparacoes.\n", chave, n, comparacoes);
        } else {
            printf("Chave %d nao encontrada na arvore B de tamanho %d com %d comparacoes.\n", chave, n, comparacoes);
        }

        // Lembre-se de liberar a memória alocada para a árvore B quando terminar
        free(arvoreB);
    }

    return 0;
}
