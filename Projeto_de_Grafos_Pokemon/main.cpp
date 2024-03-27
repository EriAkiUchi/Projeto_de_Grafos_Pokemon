#include <iostream>
#include "TGrafo.h"

int main() {
	
	TGrafo grafo(3);
	grafo.insereA(0, 1, 2.0);
	grafo.insereA(1, 2, 0.5);
	grafo.insereA(2, 0, 2.0);

	grafo.show();
	
	return 0;
}