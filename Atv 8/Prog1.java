import java.util.ArrayList;

public class XGrafo {
    private int numeroVertices;
    private int[][] matrizAdjacencia;

    // método construtor inicializa o número de vértices e todas as posições das
    // matriz adjacência com 0
    public XGrafo(int vertices) {
        matrizAdjacencia = new int[vertices][vertices];
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                matrizAdjacencia[i][j] = 0;
            }
        }
        numeroVertices = vertices;
    }

    // método que insere na matriz de adjacência uma nova aresta com seu determinado
    // peso
    public void insereAresta(int vertice1, int vertice2, int peso) {
        this.matrizAdjacencia[vertice1][vertice2] = peso;
    }

    // método que verifica se determinada aresta entre vértices existe
    public boolean existeAresta(int vertice1, int vertice2) {
        return (this.matrizAdjacencia[vertice1][vertice2] != 0);
    }

    // método que retorna a lista de vértices adjacentes a determinado vértice
    public ArrayList<Integer> listaDeAdjacencia(int vertice1) {
        ArrayList<Integer> lista = new ArrayList<>();
        for (int i = 0; i < this.numeroVertices; i++) {
            if (this.matrizAdjacencia[vertice1][i] > 0)
                lista.add(i);
        }
        return lista;
    }

    // método que retorna o peso de uma aresta
    public int getPeso(int vertice1, int vertice2) {
        return this.matrizAdjacencia[vertice1][vertice2];
    }

    public int getNumeroVertices() {
        return numeroVertices;
    }

    public int[][] getMatrizAdjacencia() {
        return matrizAdjacencia;
    }
}



import java.util.ArrayList;
import java.util.HashSet;

public class XCiclo {
    private int[] distanciaProfundidade;
    private int[] verticePredecessor;
    private XGrafo grafo;
    private final int[] distanciaCMC;
    private final int[] verticeAntecessorCMC;

    public XCiclo(int vertices, XGrafo grafo) {
        distanciaProfundidade = new int[vertices];
        verticePredecessor = new int[vertices];
        distanciaCMC = new int[vertices];
        verticeAntecessorCMC = new int[vertices];
        this.grafo = grafo;
    }

    public ArrayList<Integer> iniciaCaminhoMaisCurto(int verticeInicial, int verticeFinal) {
        caminhoMaisCurto(verticeInicial);
        return obterCaminho(verticeInicial, verticeFinal);
    }

    private ArrayList<Integer> obterCaminho(int verticeInicial, int verticeFinal) {
        ArrayList<Integer> caminho = new ArrayList<>();
        int verticeAtual = verticeFinal;
        while (verticeAtual != verticeInicial) {
            caminho.add(verticeAtual);
            verticeAtual = verticeAntecessorCMC[verticeAtual];
        }
        caminho.add(verticeInicial);
        return caminho;
    }

    public void imprimirCaminhoMaisCurto(ArrayList<Integer> caminho) {
        int tamanho = caminho.size();
        System.out.println("CAMINHO(Vertice,peso):");
        for (int i = tamanho - 1; i >= 0; i--) {
            System.out.print("(v: " + caminho.get(i));
            if (i > 0) {
                int proximoVertice = caminho.get(i - 1);
                int pesoAresta = grafo.getPeso(caminho.get(i), proximoVertice);
                System.out.print(",p:" + pesoAresta + ") -> ");
            }
        }
        System.out.print(")\n");
    }

    public int[] getDistanciaProfundidade() {
        return distanciaProfundidade;
    }

    public int[] getVerticePredecessor() {
        return verticePredecessor;
    }

    public int[] iniciaCaminhoMaisCurto(int verticeInicial) {
        caminhoMaisCurto(verticeInicial);
        return this.distanciaCMC;
    }

    private void caminhoMaisCurto(int verticeInicial) {
        for (int v = 0; v < this.grafo.getNumeroVertices(); v++) {
            this.distanciaCMC[v] = Integer.MAX_VALUE;
            this.verticeAntecessorCMC[v] = -1;
        }
        HashSet<Integer> vertices = new HashSet<>();
        this.distanciaCMC[verticeInicial] = 0;
        XGrafo Q = this.grafo;
        while (vertices.size() != Q.getNumeroVertices()) {
            int u = extrairMin(Q, vertices);
            vertices.add(u);
            for (int v : Q.listaDeAdjacencia(u)) {
                if (distanciaCMC[v] > distanciaCMC[u] + Q.getPeso(u, v)) {
                    distanciaCMC[v] = distanciaCMC[u] + Q.getPeso(u, v);
                    // System.out.println("xd"+u);
                    verticeAntecessorCMC[v] = u;
                }
            }
        }
    }

    public int[] getVerticeAntecessorCMC() {
        return verticeAntecessorCMC;
    }

    // metodo que extrai a menor distancia de s até cada vértice
    private int extrairMin(XGrafo Q, HashSet vertices) {
        int menor = Integer.MAX_VALUE;
        int vertice = -1;
        for (int i = 0; i < Q.getNumeroVertices(); i++) {
            if (menor >= distanciaCMC[i] && !vertices.contains(i)) {
                vertice = i;
                menor = distanciaCMC[i];
            }
        }
        return vertice;
    }
}
