#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <stack>

#include "TGrafo.h"

// Construtor do TGrafo, responsavel por 
TGrafo::TGrafo(int n) {
    this->n = n;
    this->m = 0;
    // aloca da matriz do TGrafo
    float** adjac = new float* [n];
    for (int i = 0; i < n; i++)
        adjac[i] = new float[n];
    adj = adjac;
    // Inicia a matriz com zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = INT_MAX;
}

// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafo::~TGrafo() {
    for (int i = 0; i < n; i++)
        delete[] adj[i];
    n = 0;
    m = 0;
    delete[] adj;
    std::cout << "espaco liberado" << std::endl;
}

// Insere uma aresta no Grafo tal que
// v eh adjacente a w
void TGrafo::insereA(int v, int w, float value) {
    // testa se nao temos a aresta
    if (adj[v][w] == INT_MAX) {
        adj[v][w] = value;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w, float value) {
    // testa se temos a aresta
    if (adj[v][w] == value) {
        adj[v][w] = INT_MAX;
        m--; // atualiza qtd arestas
    }
}

// Apresenta o Grafo contendo
// numero de vertices, arestas
// e a matriz de adjacencia obtida
void TGrafo::show() {
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (adj[i][w] != INT_MAX)
                std::cout << "Adj[" << i << "," << w << "]= " << adj[i][w] << " ";
            else std::cout << "Adj[" << i << "," << w << "]= inf" << " ";
    }
    std::cout << "\nfim da impressao do grafo." << std::endl;
}

void TGrafo::removeV(int v) {
    if (v < 0 || v >= n) {
        std::cout << "Vertice invalido\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (adj[v][i] != INT_MAX) {
            adj[v][i] = INT_MAX;
            m--;
        }
    }

    // Remove a linha v
    delete[] adj[v];

    // Remove a coluna v
    for (int i = 0; i < n; ++i) {
        for (int j = v; j < n - 1; ++j) {
            adj[i][j] = adj[i][j + 1];
        }
    }

    // Remove a entrada adj[n-1][v]
    for (int i = v; i < n - 1; ++i) {
        adj[i] = adj[i + 1];
    }

    // Atualiza o n�mero de vertices
    n--;
}