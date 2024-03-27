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
	void removeA(int v, int w, float value);
	void show();
	void removeV(int v);

};

#endif
