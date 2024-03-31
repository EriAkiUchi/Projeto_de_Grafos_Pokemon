#ifndef ___GRAFO_MATRIZ_ADJACENCIA_ROTULADO___

#define ___GRAFO_MATRIZ_ADJACENCIA_ROTULADO___

#include <vector>
#include <stack>


class TGrafo {
private:
	int n; // quantidade de vertices
	int m; // quantidade de arestas
	float** adj; //matriz de adjacencia
public:
	TGrafo(int n);
	~TGrafo();
	void insereA(int v, int w, float value);
	void removeA(int v, int w);
	void insereV();
	void show();
	void removeV(int v);

	int categoriaConexidade();
	//-----------------------------------------------------------------------------
	bool fortementeConexo();
	bool ehAlcancavel(int comeco, int fim);
	bool ehAlcancavelAuxiliar(int comeco, int fim, bool* visitado);
	//-----------------------------------------------------------------------------
	bool semiFortementeConexo();
	bool alcancavel(int comeco, int fim);
	//-----------------------------------------------------------------------------
	bool ehConexo();
	void grafoDirecionadoParaNaoDIrecionado();
	//-----------------------------------------------------------------------------
	TGrafo& matrizReduzida();
	std::vector<std::vector<int>> obterComponentesFConexos(float** adj);
	void buscaProfund1(float** adj, int k, std::stack<int>& pilha, std::vector<bool>& visitado, int n);
	void buscaProfund2(float** adj, int k, std::vector<bool>& visitado, std::vector<int>& scc, int n);
	void RecountA();
};

#endif
