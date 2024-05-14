#ifndef ___GRAFO_MATRIZ_ADJACENCIA_ROTULADO___

#define ___GRAFO_MATRIZ_ADJACENCIA_ROTULADO___

#include <vector>
#include <stack>

/*
Eric Akio Uchiyamada						RA: 10395287
Pedro Loureiro Morone Branco Volpe			RA: 10395922
Oliver Kieran Galvão McCormack				RA: 10395672
*/

class TGrafo {
private:
	int n; // quantidade de vertices
	int m; // quantidade de arestas
	int graphType;
	std::vector<std::string> pokeTypes; // vetor para armazenar o peso dos vertices (tipos de pokemon)
	std::string pokeGraphType; // string para definir o tipo do grafo, isto é, para definir quais tipos combinados serão analizados
	float** adj; //matriz de adjacencia

public:
	TGrafo(int n, std::string graphType);
	~TGrafo();

	void insereVName(int v, std::string name);

	void insereA(int v, int w, float value);
	void removeA(int v, int w);
	void insereV();
	void show();
	void showReduzido();
	void showMatrizSemRotulo();
	void removeV(int v);
	void storeFile();

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
	//-----------------------------------------------------------------------------
	void coloracaoSequencia();
	void printVertexDegree(const std::string& type);
	void getWeaknessesAndAdvantages(const std::string& type);
	int findTypeIndex(const std::string& type);
};

#endif
