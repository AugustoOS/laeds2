#include <stdio.h>
#include <stdbool.h>
#define MAX_VERTICES 100
// Classe XGrafo para manipular a matriz de adjacência de um grafo
typedef struct
{
    int matriz[MAX_VERTICES][MAX_VERTICES];   // Matriz de adjacência
    para representar o grafo int numVertices; // Número de vértices no grafo
} XGrafo;
// Função para inicializar o grafo com zeros
void inicializarGrafo(XGrafo *grafo, int numVertices)
{
    grafo->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            grafo->matriz[i][j] = 0; // Inicializa a matriz com zeros
        }
    }
}
// Função para inserir uma aresta entre dois vértices
void insereAresta(XGrafo *grafo, int vertice1, int vertice2)
{
    if (vertice1 < grafo->numVertices && vertice2 < grafo->numVertices)
    {
        grafo->matriz[vertice1][vertice2] = 1;
        grafo->matriz[vertice2][vertice1] = 1;
        // Define a posição correspondente na matriz como 1 para
        representar a aresta
    }
}
// Função para retirar uma aresta entre dois vértices
void retiraAresta(XGrafo *grafo, int vertice1, int vertice2)
{
    if (vertice1 < grafo->numVertices && vertice2 < grafo->numVertices)
    {
        grafo->matriz[vertice1][vertice2] = 0;
        grafo->matriz[vertice2][vertice1] = 0;
        // Define a posição correspondente na matriz como 0 para
        retirar a aresta
    }
}
// Classe XCiclo para verificar se um grafo possui ciclos
typedef struct
{
    bool visitado[MAX_VERTICES]; // Marca os vértices visitados
    bool pilhaRecursao[MAX_VERTICES];