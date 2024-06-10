#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Número máximo de vértices no grafo
#define V 100

// Função auxiliar para encontrar o vértice com a chave mínima
int minKey(int key[], bool mstSet[], int n) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Função para imprimir a Árvore Geradora Mínima e seu peso
void printMST(int parent[], int graph[V][V], int n) {
    printf("Aresta   Peso\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d    %d\n", parent[i], i, graph[i][parent[i]]);
    }
}

// Função para encontrar a Árvore Geradora Mínima utilizando o algoritmo de Prim
void primMST(int graph[V][V], int n) {
    int parent[V];  // Array para armazenar a Árvore Geradora Mínima
    int key[V];     // Chaves usadas para escolher a aresta de menor peso
    bool mstSet[V]; // Conjunto para armazenar os vértices já incluídos na Árvore Geradora Mínima

    // Inicialização
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // A primeira chave sempre é 0, pois o primeiro vértice é escolhido como raiz
    key[0] = 0;
    parent[0] = -1; // Nenhum vértice na Árvore Geradora Mínima

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = true;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Imprimir a Árvore Geradora Mínima e seu peso
    printMST(parent, graph, n);
}

int main() {
    int n; // Número de vértices do grafo

    printf("Informe o numero de vertices do grafo: ");
    scanf("%d", &n);

    int graph[V][V];
    printf("Informe a matriz de adjacencia (com peso) do grafo:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (i != j) { // Evita a entrada de peso para a aresta entre um vértice e ele mesmo
                printf("Peso da aresta entre o vertice %d e o vertice %d: ", i, j);
                scanf("%d", &graph[i][j]);
            } else {
                graph[i][j] = 0; // Defina 0 para a aresta entre um vértice e ele mesmo
            }
        }
    }

    // Encontre e imprima a Árvore Geradora Mínima
    primMST(graph, n);

    return 0;
}