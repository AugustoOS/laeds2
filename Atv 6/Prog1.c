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
    bool visitado[MAX_VERTICES];      // Marca os vértices visitados
    bool pilhaRecursao[MAX_VERTICES]; // Marca os vértices na pilha de
    recursão
} XCiclo;
// Função utilitária para verificar ciclos em um grafo
bool possuiCicloUtil(XGrafo *grafo, int vertice, int pai, XCiclo *ciclo)
{
    ciclo->visitado[vertice] = true;
    ciclo->pilhaRecursao[vertice] = true;
    for (int i = 0; i < grafo->numVertices; i++)
    {
        if (grafo->matriz[vertice][i])
        {
            if (!ciclo->visitado[i])
            {
                if (possuiCicloUtil(grafo, i, vertice, ciclo))
                {
                    return true; // Encontrou um ciclo
                }
            }
            else if (ciclo->pilhaRecursao[i])
            {
                return true; // Vértice i já está na pilha de recursão,
                indicando um ciclo
            }
        }
    }
    ciclo->pilhaRecursao[vertice] = false; // Remove o vértice da pilha
    de recursão return false;              // Não encontrou ciclo a partir deste vértice
}
// Função para verificar se o grafo possui ciclos
bool possuiCiclo(XGrafo *grafo)
{
    XCiclo ciclo;
    for (int i = 0; i < grafo->numVertices; i++)
    {
        ciclo.visitado[i] = false;      // Inicializa o vetor de visitados
        ciclo.pilhaRecursao[i] = false; // Inicializa o vetor de pilha
        de recursão
    }
    for (int i = 0; i < grafo->numVertices; i++)
    {
        if (!ciclo.visitado[i])
        {
            if (possuiCicloUtil(grafo, i, -1, &ciclo))
            {
                return true; // Encontrou um ciclo em algum ponto
            }
        }
    }
    return false; // Não encontrou ciclos no grafo
}
int main()
{
    XGrafo grafo;
    int numVertices = 7;
    inicializarGrafo(&grafo, numVertices);
    insereAresta(&grafo, 0, 1);
    insereAresta(&grafo, 0, 3);
    insereAresta(&grafo, 0, 4);
    insereAresta(&grafo, 2, 6);
    insereAresta(&grafo, 2, 1);
    insereAresta(&grafo, 2, 3);
    insereAresta(&grafo, 3, 7);
    insereAresta(&grafo, 4, 5);
    insereAresta(&grafo, 4, 7);
    insereAresta(&grafo, 5, 6);
    insereAresta(&grafo, 6, 7);
    if (possuiCiclo(&grafo))
    {
        printf("O grafo possui ciclos.\n");
    }
    else
    {
        printf("O grafo não possui ciclos.\n");
    }
    return 0;
}