#include "Executor.h"
#include "Graph.h"
#include "GraphVisit.h"

#include <iostream>
#include <fstream>
#include <cmath>

Executor::Executor() {}

Executor::~Executor() {};

void Executor::run() {
	while(true){
		int nummOfSensors;
		unsigned long seed;
		double p;
		//Unos pocetnih vrednosti 

		cout << "Za citanje pocetnih vrednosti sa konzole unesite 1. " << endl;
		cout << "Za citanje pocetnih vrednosti iz fajla unesite 2." << endl;
		cout << "Vrednost: ";

		int startValues;
		cin >> startValues;

		string line;
		if (startValues == 2) {
			string filename;
			cout << "Unesite naziv fajla: ";
			cin >> filename;

			ifstream file(filename);
			if (!file.is_open()) {
				cout << "Greska pri otvaranju fajla!\n";
				continue;
			}

			file >> nummOfSensors;
			if (nummOfSensors <= 0) {
				cout << "Greska, uneti broj senzora mora biti veci od nula. " << endl;
				continue;;
			}

			file >> seed;
			if (seed <= 0) {
				cout << "Greska, klica mora biti veca od nula. " << endl;
				continue;
			}

			file >> p;
			double lower = 1.0 / nummOfSensors;
			double upper = log(nummOfSensors) / nummOfSensors;
			if (p < lower || p > upper) {
				cout << "Greska, prag p nije u dozvoljenom opsegu. " << endl;
				continue;
			}

			file.close();



		}
		else if (startValues != 1 && startValues != 2) {
			cout << "Niste uneli dobru vrednost. " << endl;
			continue;
		}
		else if (startValues == 1) {

			cout << "Unesite broj senzora: ";
			cin >> nummOfSensors;
			if (nummOfSensors <= 0) {
				cout << "Greska, uneti broj senzora mora biti veci od nula. " << endl;
				continue;
			}

			cout << "Unesite klicu za generator (klica mora biti celobrojna vrednost veca od nule): ";
			cin >> seed;
			if (seed <= 0) {
				cout << "Greska, klica mora biti veca od nula. " << endl;
				continue;
			}
		
			double lower = 1.0 / nummOfSensors;
			double upper = log(nummOfSensors) / nummOfSensors;
			cout << "Potrebno je uneti prag p, koji je u granicama " << "[" << lower << ", " << upper << "]." << endl;
			cout << "Unesite prag p: ";
			cin >> p;
			if (p < lower || p > upper) {
				cout << "Greska, prag p nije u dozvoljenom opsegu. " << endl;
				continue;
			}
		}

		Graph graph(nummOfSensors, seed, p);
		graph.graphCreate();
		GraphVisit graphVisit(graph);
	
		while(true){

			int option = options();
			if (option == -1) continue;

			if (option == 1) {
				addSensorToGraph(graph);
			}
			else if (option == 2) {
				removeSensor(graph);
			}
			else if (option == 3) {
				printMatrix(graph);
			}
			else if (option == 4) {
				printGraph(graph);
			}


			if (option == 5) {
				visit1(graphVisit);
			}

			else if (option == 6) {
				visit2(graphVisit);
			}
			else if (option == 7) {
				eccentricity(graphVisit);
			}
			else if (option == 8) {
				minTravelTime(graphVisit);
			}

			if (option == 9) {
				break;
			}
		}
		int n;
		cout << "Ako zelite da kreirate novi graf pritisnite 1." << endl;
		cout << "Ako zelite da prekinete program pritisnite neki drugi broj." << endl;
		cin >> n;
		if (n == 1) continue;
		else return;
	}
}

int Executor::options() {
	cout << "Unesite redni broj opcije koje zelite da izvrsite: " << endl;

	int option;
	cout << "1. Dodavanje senzora u graf." << endl <<
		"2. Brisanje senzora iz grafa." << endl <<
		"3. Ispis matrice senzora." << endl <<
		"4. Ispis grafa." << endl <<
		"5. Obilazak grafa (BFS)" << endl <<
		"6. Obilazak grafa (DFS)" << endl <<
		"7. Odredjivanje eksentricnosti svakog cvora. " << endl <<
		"8. Odredivanje najkraceg vremena putovanja signala izmedju dva zadata senzora. " << endl <<
		"9. Prekid programa." << endl;

	cout << "Opcija: ";
	cin >> option;
	if (1 > option || option > 9) {
		cout << "Unesite validnu opciju! " << endl;
		return -1;
	}
	return option;
}

void Executor::addSensorToGraph(Graph& graph) {
	cout << "Unesite id senzora koji zelite da dodate: ";
	int id;
	cin >> id;

	graph.addSensorToGraph(id);
}

void Executor::removeSensor(Graph& graph) {
	cout << "Unesite id senzora koji zelite da uklonite: ";
	int id;
	cin >> id;

	graph.removeSensor(id);
}

void Executor::printMatrix(Graph& graph) {
	graph.printMatrix();
}

void Executor::printGraph(Graph& graph) {
	graph.printGraph();
}

void Executor::visit1(GraphVisit& graphVisit) {
	cout << "Unesite id senzora: ";
	int id;
	cin >> id;

	graphVisit.visit(1, id);
}
void Executor::visit2(GraphVisit& graphVisit) {
	cout << "Unesite id senzora: ";
	int id;
	cin >> id;

	graphVisit.visit(2, id);
}

void Executor::eccentricity(GraphVisit& graphVisit) {
	graphVisit.eccentricity();
}

void Executor::minTravelTime(GraphVisit& graphVisit) {
	cout << "Unesite id pocetnog i krajnjeg senzora: ";
	int id1;
	cin >> id1;
	int id2;
	cin >> id2;

	graphVisit.minTravelTime(id1, id2);
}

