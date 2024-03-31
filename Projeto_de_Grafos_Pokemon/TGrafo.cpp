#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
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
void TGrafo::removeA(int v, int w) {
    // testa se temos a aresta
    if (adj[v][w] != INT_MAX) {
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

    // Atualiza o numero de vertices
    n--;
}

void TGrafo::insereV() {
    int vertice = this->n;
    std::cout << "Indice do novo vertice: " << vertice;
    int novoTamanho = vertice + 1;

    float** novaMatriz = new float* [novoTamanho];
    float** matrizAntiga = this->adj;
    
    for (int i = 0;i < novoTamanho;i++) {
        novaMatriz[i] = new float[novoTamanho];
        for (int j = 0;j < novoTamanho;j++) {
            if (i < vertice && j < vertice) {
                //copiar a matriz antiga
                novaMatriz[i][j] = matrizAntiga[i][j];
            }
            else {
                //iniciar como infinito
                novaMatriz[i][j] = INT_MAX;
            }
        }
    }

    for (int i = 0;i < this->n;i++) {
        delete[] matrizAntiga[i];
    }
    delete[] matrizAntiga;

    this->adj = novaMatriz;
    this->n = novoTamanho;
    
}
//Exercicio 9
int TGrafo::categoriaConexidade() {
    if (fortementeConexo())
        return 3;
    else if (semiFortementeConexo())
        return 2;
    else if (ehConexo())
        return 1;
    else return 1;
}
//-----------------------------------------------------------------------------
bool TGrafo::fortementeConexo() {
    for (int i = 0;i < this->n;i++) {
        for (int j = 0;j < this->n;j++) {
            if (i != j && (ehAlcancavel(i, j) || ehAlcancavel(j, i))) {
                return false;
            }
        }
    }
    return true;
}

//verifica se comeco eh alcancavel em fim
bool TGrafo::ehAlcancavel(int comeco, int fim) {
    bool* visitado = new bool[n] {false};//novo vetor de tamanho n iniciado como false
    bool resultado = ehAlcancavelAuxiliar(comeco,fim,visitado);
    delete[] visitado;
    return resultado;
}

bool TGrafo::ehAlcancavelAuxiliar(int comeco, int fim, bool* visitado) {
    if (comeco == fim)
        return true;

    visitado[comeco] = true;

    for (int i = 0;i < this->n;i++) {
        if (!visitado[i] && adj[comeco][i] == INT_MAX) {
            if (ehAlcancavelAuxiliar(i, fim, visitado))
                return true;
        }
    }

    return false;
}
//-----------------------------------------------------------------------------
//para cada par(i, j), verifica se existe um caminho direcionado para i,j ou j,i
bool TGrafo::semiFortementeConexo() {
    for (int i = 0;i < this->n;i++) {
        for (int j = 0;j < this->n;j++) {
            if (i != j && !alcancavel(i, j) && !alcancavel(j, i))
                return false;
        }
    }
    return true;
}

bool TGrafo::alcancavel(int comeco, int fim) {
    //verifica se existe um caminho do comeco para o fim
    std::vector<bool> visitado(n, false);
    std::stack<int> pilha;

    pilha.push(comeco);
    visitado[comeco] = true;

    while (!pilha.empty()) { //percorre os vizinhos de v atual
        int atual = pilha.top();
        pilha.pop();

        //verifica se existe uma aresta direcionada de v atual e vizinhos nao vizitados
        for (int vizinho = 0;vizinho < this->n;vizinho++) {
            if (adj[atual][vizinho] != INT_MAX && !visitado[vizinho]) {
                
                pilha.push(vizinho);
                visitado[vizinho] = true;

                //se o vizinho ja for o destino, ja esta conectado diretamente
                if (vizinho == fim)
                    return true;
            }
        }
    }
    return false;
}
//-----------------------------------------------------------------------------
//verifica se o grafo eh Conexo
bool TGrafo::ehConexo() {

    //criando uma copia do grafo original
    float** grafoOriginal = new float* [n];
    for (int i = 0;i < this->n;i++) {
        grafoOriginal[i] = new float[n];
        
        for (int j = 0;j < this->n;j++)
            grafoOriginal[i][j] = adj[i][j];
    }

    //transformar o grafo direcionado para nao direcionado, ja que eh para apenas verificar conexoes
    grafoDirecionadoParaNaoDIrecionado();
    std::vector<bool> visitado(n, false);
    std::queue<int> fila;

    if (this->n == 0) {
        std::cout << "grafo esta vazio!\n";
        return 0; //grafo eh considerado conexo
    }

    //inicia busca em largura
    fila.push(0);
    visitado[0] = true;

    //realiza busca
    while (!fila.empty()) {
        int vertice = fila.front();
        fila.pop();

        //percorre todos os vizinhos
        for (int vizinho = 0;vizinho < this->n;vizinho++) {
            if (adj[vertice][vizinho] != INT_MAX && !visitado[vizinho]) {
                fila.push(vizinho);
                visitado[vizinho] = true;
            }
        }
    }

    this->adj = grafoOriginal;//volta a ser direcionado

    //verifica se todos os vertices foram visitados
    for (bool i : visitado) {
        if (i == false) {
            return false;
        }
    }
    return true;
}

void TGrafo::grafoDirecionadoParaNaoDIrecionado() {
    for (int i = 0;i < this->n;i++) {
        for (int j = 0;j < this->n;j++) {
            if (this->adj[i][j] != INT_MAX)
                this->adj[j][i] = this->adj[i][j];
        }
    }
}
//-----------------------------------------------------------------------------
TGrafo& TGrafo::matrizReduzida() {
    std::vector<std::vector<int>> scc = obterComponentesFConexos(this->adj); //determinar os componentes fortemente conexos

    int tamanho = scc.size(); //tamanho da matriz nova

    float** sccMatriz = new float* [tamanho];
    for (int i = 0; i < tamanho; ++i) {
        sccMatriz[i] = new float[tamanho];
        for (int j = 0; j < tamanho; ++j)
            sccMatriz[i][j] = INT_MAX;  // inicializando matriz nova
    }

    // Itera em cada componente fortemente conectado
    for (int i = 0; i < tamanho; ++i) {

        // Itera em cada vertice do componente fortemente conectado
        for (int k : scc[i]) {

            // checa quem tinha aresta com ele na matrix original
            for (int vizinho = 0; vizinho < n; ++vizinho) {

                //se tinha aresta na matriz original
                if (this->adj[k][vizinho] != 0) {

                    //acha qual o componente com qual ele tem uma aresta
                    for (int j = 0; j < tamanho; ++j) {

                        // se achar o componente:
                        if (std::find(scc[j].begin(), scc[j].end(), vizinho) != scc[j].end()) {

                            // checa antes se não é ele mesmo
                            if (i != j) {
                                sccMatriz[i][j] = 1; //adiciona a aresta na matriz nova
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    TGrafo* grafoReduzido = new TGrafo(tamanho);
    grafoReduzido->adj = sccMatriz;
    grafoReduzido->n = (tamanho);
    grafoReduzido->RecountA();
    return *grafoReduzido;
}

std::vector<std::vector<int>> TGrafo::obterComponentesFConexos(float** adj) {
    int n = this->n;
    std::stack<int> pilha;
    std::vector<bool> visitado(n, false);

    //Busca em profundidade
    for (int k = 0; k < n; ++k)
        if (!visitado[k])
            buscaProfund1(adj, k, pilha, visitado, n);

    //Cria um grafo reverso
    float** reverse_adj_matrix = new float* [n];
    for (int i = 0; i < n; ++i)
        reverse_adj_matrix[i] = new float[n];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            reverse_adj_matrix[i][j] = adj[j][i];

    //Pop de todos os vertices da pilha e faz busca em profundidade no grafo invertido
    visitado.assign(n, false);//setar vetor inteiro como falso
    std::vector<std::vector<int>> componentes_fortemente_conectados;
    while (!pilha.empty())
    {
        int k = pilha.top();
        pilha.pop();
        if (!visitado[k])
        {
            std::vector<int> scc;
            buscaProfund2(reverse_adj_matrix, k, visitado, scc, n);
            componentes_fortemente_conectados.push_back(scc);
        }
    }
    return componentes_fortemente_conectados;
}

void TGrafo::buscaProfund1(float** adj, int k, std::stack<int>& pilha, std::vector<bool>& visitado, int n) {
    visitado[k] = true;
    for (int vizinho = 0; vizinho < n; ++vizinho)
        if (adj[k][vizinho] != 0 && !visitado[vizinho])
            buscaProfund1(adj, vizinho, pilha, visitado, n);

    pilha.push(k);
}

void TGrafo::buscaProfund2(float** adj, int k, std::vector<bool>& visitado, std::vector<int>& scc, int n) {
    visitado[k] = true;
    scc.push_back(k);
    for (int vizinho = 0; vizinho < n; ++vizinho)
        if (adj[k][vizinho] != 0 && !visitado[vizinho])
            buscaProfund2(adj, vizinho, visitado, scc, n);

}

void TGrafo::RecountA()//essa reconta as arestas
{
    this->m = 0;
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            if (this->adj[i][j] != 0)
                m++;
}