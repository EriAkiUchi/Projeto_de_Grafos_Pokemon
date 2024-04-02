#include <iostream>
#include <fstream>
#include <string>
#include "TGrafo.h"

// Função para ler um arquivo .txt personalizado de entrada
TGrafo& readFile(std::string fileName) {
	std::ifstream file;
	std::string line;
	file.open(fileName); // Abre o arquivo para leitura

	std::getline(file, line); // Linha para ler o tipo do grafo (no nosso caso tipo 7) 
	std::getline(file, line); // Linha para ler o tipo de pokemon a ser analizado 
	std::string newPokeGraphType = line;
	std::getline(file, line); // Linha para receber a quantidade de vértices 
	int numVertic = std::stoi(line);
	TGrafo* newGraph = new TGrafo(numVertic, newPokeGraphType);

	//
	int i = 0;
	int vertice;
	std::string verticeNome;
	if (file.is_open()) {
		while (i < numVertic) {
			file >> vertice >> verticeNome;
			verticeNome.erase(remove(verticeNome.begin(), verticeNome.end(), ' '), verticeNome.end()); // Remove possiveis espaços da string
			newGraph->insereVName(vertice, verticeNome);
			i++;
		}
	}
	else {
		std::cout << "Couldn't open file\n";
	}

	file >> line; // Linha para ler o numero de arestas
	int numA = std::stoi(line);
	int vertice1, vertice2; float peso;
	i = 0;
	if (file.is_open()) {
		while (i < numA) {
			file >> vertice1 >> vertice2 >> peso;
			newGraph->insereA(vertice1, vertice2, peso);
			i++;
		}
	}
	else {
		std::cout << "Couldn't open file\n";
	}

	return *newGraph;
}

void printFile(std::string fileName) {
	std::ifstream file;
	std::string line;
	file.open(fileName); // Abre o arquivo para leitura
	if (file.is_open()) {
		while (file) {
			std::getline(file, line);
			std::cout << line << std::endl;
		}
	}
}

int main() {
	
	// Inicialização dos grafos
	std::string fileName;
	TGrafo grafoSteel(0, "null");
	TGrafo grafoGhost(0, "null");
	TGrafo grafoGrass(0, "null");
	TGrafo grafoFire(0, "null");
	TGrafo grafoNovo(0, "null");
	//
	TGrafo grafoReduzidoSteel(0, "null");
	TGrafo grafoReduzidoGhost(0, "null");
	TGrafo grafoReduzidoGrass(0, "null");
	TGrafo grafoReduzidoFire(0, "null");
	TGrafo grafoReduzidoNovo(0, "null");
	//
	int vertice_origem, vertice_chegada; float valor_aresta;
	int categoria_conexidade;
	int opcao = -1, opcaoArquivo = -1;

	do {

		std::cout << "\n****************************************************\n";
		std::cout << "*** Analise das combinações de tipos dos Pokemons ***\n"
					<< "Digite uma opcao\n"
					<< "[1] Ler dados de um arquivo e Criar Matriz de Adjacencia\n"
					<< "[2] Gravar Matriz de Adjacencia no arquivo grafo.txt\n"
					<< "[3] Inserir novo vertice\n"
					<< "[4] Inserir nova aresta\n"
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
			case 1:
				std::cout << "Qual arquivo deseja ler ?\n";
				std::cout << "Digite um opcao\n"
						  << "[1] Arquivo do grafo tipo Metal (Steel)\n"
					      << "[2] Arquivo do grafo tipo Fantasma (Ghost)\n"
					      << "[3] Arquivo do grafo tipo Grama (Grass)\n"
					      << "[4] Arquivo do grafo tipo Fogo (Fire)\n"
					      << "[5] Novo arquivo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
					 case 1:
						 grafoSteel = readFile("Steel.txt");
						 break;
					 case 2:
						 grafoGhost = readFile("Ghost.txt");
						 break;
					 case 3:
						 grafoGrass = readFile("Grass.txt");
						 break;
					 case 4:
						 grafoFire = readFile("Fire.txt");
						 break;
					 case 5:
						 std::cout << "Digite o path do arquivo: \n";
						 std::cin >> fileName;
						 grafoNovo = readFile(fileName);
						 break;
				}
				break;

			case 2:
				std::cout << "Qual arquivo deseja salvar ?\n";
				std::cout << "Digite um opcao\n"
					<< "[1] Arquivo do grafo tipo Metal (Steel)\n"
					<< "[2] Arquivo do grafo tipo Fantasma (Ghost)\n"
					<< "[3] Arquivo do grafo tipo Grama (Grass)\n"
					<< "[4] Arquivo do grafo tipo Fogo (Fire)\n"
					<< "[5] Novo arquivo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
				case 1:
					grafoSteel.storeFile();
					std::cout << "Grafo Steel salvo em grafo.txt\n";
					break;
				case 2:
					grafoGhost.storeFile();
					std::cout << "Grafo Ghost salvo em grafo.txt\n";
					break;
				case 3:
					grafoGrass.storeFile();
					std::cout << "Grafo Grass salvo em grafo.txt\n";
					break;
				case 4:
					grafoFire.storeFile();
					std::cout << "Grafo Fire salvo em grafo.txt\n";
					break;
				case 5:
					grafoNovo.storeFile();
					break;
				}
				break;
			case 3:
				std::cout << "Qual grafo deseja inserir o vertice ?\n";
				std::cout << "Digite um opcao\n"
					<< "[1] Grafo tipo Metal (Steel)\n"
					<< "[2] Grafo tipo Fantasma (Ghost)\n"
					<< "[3] Grafo tipo Grama (Grass)\n"
					<< "[4] Grafo tipo Fogo (Fire)\n"
					<< "[5] Novo Grafo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
					case 1:
						grafoSteel.insereV();
						break;
					case 2:
						grafoGhost.insereV();
						break;
					case 3:
						grafoGrass.insereV();
						break;
					case 4:
						grafoFire.insereV();
						break;
					case 5:
						grafoNovo.insereV();
						break;
				}
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

				std::cout << "Qual grafo deseja inserir a aresta ?\n";
				std::cout << "Digite um opcao\n"
					<< "[1] Grafo tipo Metal (Steel)\n"
					<< "[2] Grafo tipo Fantasma (Ghost)\n"
					<< "[3] Grafo tipo Grama (Grass)\n"
					<< "[4] Grafo tipo Fogo (Fire)\n"
					<< "[5] Novo Grafo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
					case 1:
						grafoSteel.insereA(vertice_origem, vertice_chegada, valor_aresta);
						break;
					case 2:
						grafoGhost.insereA(vertice_origem, vertice_chegada, valor_aresta);
						break;
					case 3:
						grafoGrass.insereA(vertice_origem, vertice_chegada, valor_aresta);
						break;
					case 4:
						grafoFire.insereA(vertice_origem, vertice_chegada, valor_aresta);
						break;
					case 5:
						grafoNovo.insereA(vertice_origem, vertice_chegada, valor_aresta);
						break;
				}
				std::cout << "\nFoi inserido um nova aresta no final do grafo";
				break;

			case 5:
				std::cout << "\nDigite um vertice para apagar: ";
				std::cin >> vertice_origem;

				std::cout << "Qual grafo deseja remover o vertice ?\n";
				std::cout << "Digite um opcao\n"
					<< "[1] Grafo tipo Metal (Steel)\n"
					<< "[2] Grafo tipo Fantasma (Ghost)\n"
					<< "[3] Grafo tipo Grama (Grass)\n"
					<< "[4] Grafo tipo Fogo (Fire)\n"
					<< "[5] Novo Grafo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
				case 1:
					grafoSteel.removeV(vertice_origem);
					break;
				case 2:
					grafoGhost.removeV(vertice_origem);
					break;
				case 3:
					grafoGrass.removeV(vertice_origem);
					break;
				case 4:
					grafoFire.removeV(vertice_origem);
					break;
				case 5:
					grafoNovo.removeV(vertice_origem);
					break;
				}
				std::cout << "\nVertice foi removido do grafo";
				break;

			case 6:
				std::cout << "\nDigite o vertice de origem: ";
				std::cin >> vertice_origem;
				std::cin.ignore();

				std::cout << "\nDigite o vertice de chegada: ";
				std::cin >> vertice_chegada;
				std::cin.ignore();

				std::cout << "Qual grafo deseja remover a aresta ?\n";
				std::cout << "Digite um opcao\n"
					<< "[1] Grafo tipo Metal (Steel)\n"
					<< "[2] Grafo tipo Fantasma (Ghost)\n"
					<< "[3] Grafo tipo Grama (Grass)\n"
					<< "[4] Grafo tipo Fogo (Fire)\n"
					<< "[5] Novo Grafo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
					case 1:
						grafoSteel.removeA(vertice_origem, vertice_chegada);
						break;
					case 2:
						grafoGhost.removeA(vertice_origem, vertice_chegada);
						break;
					case 3:
						grafoGrass.removeA(vertice_origem, vertice_chegada);
						break;
					case 4:
						grafoFire.removeA(vertice_origem, vertice_chegada);
						break;
					case 5:
						grafoNovo.removeA(vertice_origem, vertice_chegada);
						break;
				}
				std::cout << "\nAresta foi removida do grafo";
				break;

			case 7:
				std::cout << "Qual arquivo deseja mostrar ?\n";
				std::cout << "Digite um opcao\n"
						  << "[1] Arquivo do Grafo tipo Metal (Steel)\n"
					      << "[2] Arquivo do Grafo tipo Fantasma (Ghost)\n"
					      << "[3] Arquivo do Grafo tipo Grama (Grass)\n"
					      << "[4] Arquivo do Grafo tipo Fogo (Fire)\n"
					      << "[5] Arquivo do Novo Grafo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
					case 1:
						printFile("Steel.txt");
						break;
					case 2:
						printFile("Ghost.txt");
						break;
					case 3:
						printFile("Grass.txt");
						break;
					case 4:
						printFile("Fire.txt");
						break;
					case 5:
						std::cout << "Digite o path do arquivo: \n";
						std::cin >> fileName;
						printFile(fileName);
						break;
				}
				break;

			case 8:
				std::cout << "Qual grafo deseja mostrar ?\n";
				std::cout << "Digite um opcao\n"
						  << "[1] Grafo tipo Metal (Steel)\n"
					      << "[2] Grafo tipo Fantasma (Ghost)\n"
					      << "[3] Grafo tipo Grama (Grass)\n"
					      << "[4] Grafo tipo Fogo (Fire)\n"
					      << "[5] Novo Grafo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
					case 1:
						grafoSteel.show();
						break;
					case 2:
						grafoGhost.show();
						break;
					case 3:
						grafoGrass.show();
						break;
					case 4:
						grafoFire.show();
						break;
					case 5:
						grafoNovo.show();
						break;
				}
				std::cout << "\nGrafo printado com sucesso";
				break;

			case 9:
				std::cout << "Qual grafo deseja mostrar ?\n";
				std::cout << "Digite um opcao\n"
					<< "[1] Grafo tipo Metal (Steel)\n"
					<< "[2] Grafo tipo Fantasma (Ghost)\n"
					<< "[3] Grafo tipo Grama (Grass)\n"
					<< "[4] Grafo tipo Fogo (Fire)\n"
					<< "[5] Novo Grafo\nOption: ";
				std::cin >> opcaoArquivo;
				std::cin.ignore();
				std::cout << '\n';
				switch (opcaoArquivo) {
					case 1:
						categoria_conexidade = grafoSteel.categoriaConexidade();
						switch (categoria_conexidade) {
							case 3:
								std::cout << "\nGrafo eh Fortemente Conexo\n";
								break;
							case 2:
								std::cout << "\nGrafo eh Semi-Fortemente Conexo\n";
								break;
							case 1:
								std::cout << "\nGrafo eh Simplesmente Conexo\n";
								break;
							case 0:
								std::cout << "\nGrafo eh Desconexo\n";
								break;
						}
						grafoReduzidoSteel = grafoSteel.matrizReduzida();
						grafoReduzidoSteel.showReduzido();
						break;
					
					case 2:
						categoria_conexidade = grafoGhost.categoriaConexidade();
						switch (categoria_conexidade) {
							case 3:
								std::cout << "\nGrafo eh Fortemente Conexo\n";
								break;
							case 2:
								std::cout << "\nGrafo eh Semi-Fortemente Conexo\n";
								break;
							case 1:
								std::cout << "\nGrafo eh Simplesmente Conexo\n";
								break;
							case 0:
								std::cout << "\nGrafo eh Desconexo\n";
								break;
						}
						grafoReduzidoGhost = grafoGhost.matrizReduzida();
						grafoReduzidoGhost.showReduzido();
						break;
					
					case 3:
						categoria_conexidade = grafoGrass.categoriaConexidade();
						switch (categoria_conexidade) {
							case 3:
								std::cout << "\nGrafo eh Fortemente Conexo\n";
								break;
							case 2:
								std::cout << "\nGrafo eh Semi-Fortemente Conexo\n";
								break;
							case 1:
								std::cout << "\nGrafo eh Simplesmente Conexo\n";
								break;
							case 0:
								std::cout << "\nGrafo eh Desconexo\n";
								break;
						}
						grafoReduzidoGrass = grafoGrass.matrizReduzida();
						grafoReduzidoGrass.showReduzido();
						break;
					
					case 4:
						categoria_conexidade = grafoFire.categoriaConexidade();
						switch (categoria_conexidade) {
							case 3:
								std::cout << "\nGrafo eh Fortemente Conexo\n";
								break;
							case 2:
								std::cout << "\nGrafo eh Semi-Fortemente Conexo\n";
								break;
							case 1:
								std::cout << "\nGrafo eh Simplesmente Conexo\n";
								break;
							case 0:
								std::cout << "\nGrafo eh Desconexo\n";
								break;
						}
						grafoReduzidoFire = grafoFire.matrizReduzida();
						grafoReduzidoFire.showReduzido();
						break;
					
					case 5:
						categoria_conexidade = grafoNovo.categoriaConexidade();
						switch (categoria_conexidade) {
							case 3:
								std::cout << "\nGrafo eh Fortemente Conexo\n";
								break;
							case 2:
								std::cout << "\nGrafo eh Semi-Fortemente Conexo\n";
								break;
							case 1:
								std::cout << "\nGrafo eh Simplesmente Conexo\n";
								break;
							case 0:
								std::cout << "\nGrafo eh Desconexo\n";
								break;
						}
					grafoReduzidoNovo = grafoNovo.matrizReduzida();
					grafoReduzidoNovo.showReduzido();
					break;
				}
				break;
		}

	} while (opcao != 0);

	return 0;
}