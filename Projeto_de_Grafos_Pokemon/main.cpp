#include <iostream>
#include "TGrafo.h"

int main() {
	
	TGrafo grafo(3);
	grafo.insereA(0, 1, 2.0);
	grafo.insereA(1, 2, 0.5);
	grafo.insereA(2, 0, 2.0);

	int vertice_origem, vertice_chegada; float valor_aresta;

	int opcao = -1;

	do {

		std::cout << "\n****************************************************\n";
		std::cout << "*** Analise das combinações de tipos dos Pokemons ***\n"
					<< "Digite uma opcao\n"
					<< "[1] Ler dados do arquivo grafo.txt e Criar Matriz de Adjacencia\n"
					<< "[2] Gravar Matriz de Adjacencia no arquivo grafo.txt\n"
					<< "[3] Inserir vertice\n"
					<< "[4] Inserir aresta\n"
					<< "[5] Remove vertice\n"
					<< "[6] Remove aresta\n"
					<< "[7] Mostrar conteudo do arquivo\n"
					<< "[8] Mostrar grafo\n"
					<< "[9] Apresentar a conexidade do grafo e o grafo reduzido\n"
					<< "[0] Encerrar a aplicacao\nOption: ";
		std::cin >> opcao;
		std::cin.ignore();
		std::cout << '\n';

		valor_aresta = 0.0;

		switch (opcao) {
			case 3:
				grafo.insereV();
				std::cout << "\nFoi inserido um novo vertice no final do grafo";
				break;

			case 4:
				std::cout << "\nDigite o vertice de origem: ";
				std::cin >> vertice_origem;
				std::cin.ignore();

				std::cout << "\nDigite o vertice de chegada: ";
				std::cin >> vertice_chegada;
				std::cin.ignore();

				std::cout << "\nDigite o valor da aresta: ";
				std::cin >> valor_aresta;
				std::cin.ignore();

				grafo.insereA(vertice_origem, vertice_chegada, valor_aresta);
				break;

			case 5:
				std::cout << "\nDigite um vertice para apagar: ";
				std::cin >> vertice_origem;
				grafo.removeV(vertice_origem);
				break;

			case 6:
				std::cout << "\nDigite o vertice de origem: ";
				std::cin >> vertice_origem;
				std::cin.ignore();

				std::cout << "\nDigite o vertice de chegada: ";
				std::cin >> vertice_chegada;
				std::cin.ignore();

				grafo.removeA(vertice_origem, vertice_chegada);
				break;

			case 8:
				grafo.show();
				break;

		}

	} while (opcao != 0);

	return 0;
}