#include "GraphVisit.h"
#include <iostream>
using namespace std;

GraphVisit::GraphVisit(const Graph& graph)
	:graph(graph),
	nummOfSensors(graph.getNummOfSensors()),
	visits(new Visit[nummOfSensors]),
	sensors(graph.getSensors()),
	indices(graph.getIndices()),
	edges(graph.getEdges()),
	bfs(new Sensor[nummOfSensors]),
	dfs(new Sensor[nummOfSensors])
{
	for (int i = 0; i < nummOfSensors; i++) {
		visits[i].sensorId = sensors.getSensor(i).id;
		visits[i].visited = false;
		visits[i].index = i;
	}
}

GraphVisit::~GraphVisit() {
	delete[] visits;
	delete[] bfs;
	delete[] dfs;
}

void GraphVisit::visit(int visitType, int startId) {
	if (visitType == 1) {
		BFS(startId);
	}
	else if (visitType == 2) {
		DFS(startId);
	}
}

void GraphVisit::resetVisits() {
	for (int i = 0; i < nummOfSensors; i++) {
		visits[i].visited = false;
	}
}

void GraphVisit::BFS(int startId) {
	if (startId < 0) return;

	//ako je visit vec koriscen resetuj za novi obilazak
	resetVisits();

	int* queue = new int[nummOfSensors];
	int startIndex = -1;
	int sensorId = startId;
	int indexForVisit = 0;

	//Pamtimo indekse pocetka i kraja reda
	int front = 0;
	int back = 0;

	for (int i = 0; i < nummOfSensors; i++) {
		if (visits[i].sensorId == startId) {
			startIndex = i;
			break;
		};
	}
	if (startIndex == -1) return; //ne postoji senzor

	//Ubacujemo u red indeks senzora koji smo posetili
	queue[back++] = startIndex;
	visits[startIndex].visited = true;
	bfs[indexForVisit++] = sensors.getSensorWithId(sensorId);

	//Izvrsavaj dok red nije razan
	while (front < back) {

		//dohvatamo indeks sensora iz reda
		int vIndex = queue[front++];
		int vId = visits[vIndex].sensorId;

		int start = indices.getSensorStartIndex(vId);
		int finish = indices.getNextEdgeIndex(vId);

		//Prolazimo sve susede naseg cvora
		for (int i = start; i < finish; i++) {

			int uId = edges.getIdAtIndex(i);
			if (uId == -1) continue;

			//Pronalazimo indeks suseda na osnovu id-ja
			for (int j = 0; j < nummOfSensors; j++) {

				//Ako smo nasli sused i ako nije posecen poseti ga
				if (visits[j].sensorId == uId && !(visits[j].visited)) {

					visits[j].visited = true;
					bfs[indexForVisit++] = sensors.getSensorWithId(uId);
					queue[back++] = j;
				}
			}
		}

	}
	delete[] queue;

	printBFS(indexForVisit);
}

void GraphVisit::DFS(int startId) {
	if (startId < 0) return;

	//ako je visit vec koriscen resetuj za novi obilazak
	resetVisits();

	int* stack = new int[nummOfSensors];
	int top = 0;
	int indexForVisit = 0;
	int sensorId = startId;

	int startIndex = -1;
	for (int i = 0; i < nummOfSensors; i++) {
		if (visits[i].sensorId == startId) {
			startIndex = i;
			sensorId = visits[i].sensorId;
			break;
		};
	}
	if (startIndex == -1) return; //ne postoji senzor

	// Ubacujemo start na stek
	stack[top++] = startIndex;
	visits[startIndex].visited = true;
	dfs[indexForVisit++] = sensors.getSensorWithId(sensorId);

	// Izvrsavaj dok stek nije prazna
	while (top > 0) {
		int vIndex = stack[--top]; //stek pokazuje na prvu slobodnu poziciju
		int vId = visits[vIndex].sensorId;

		int start = indices.getSensorStartIndex(vId);
		int finish = indices.getNextEdgeIndex(vId);

		//Prolazimo sve susede naseg cvora
		for (int i = start; i < finish; i++) {
			int uId = edges.getIdAtIndex(i);
			if (uId == -1) continue;

			//Pronalazimo indeks suseda na osnovu id-ja
			for (int j = 0; j < nummOfSensors; j++) {

				//Ako smo nasli sused i ako nije posecen poseti ga
				if (visits[j].sensorId == uId && !(visits[j].visited)) {

					visits[j].visited = true;
					dfs[indexForVisit++] = sensors.getSensorWithId(uId);
					stack[top++] = j;
				}

			}
		}
	}
	delete[] stack;

	printDFS(indexForVisit);
}

void GraphVisit::printBFS(int nummOfElem) {
	for (int i = 0; i < nummOfElem; i++) {
		cout << "[id: " << bfs[i].id << ", speed: " << bfs[i].speed << "]";
		if (i != nummOfElem - 1) cout << "->";
	}
	cout << endl;
}

void GraphVisit::printDFS(int nummOfElem) {
	for (int i = 0; i < nummOfElem; i++) {
		cout << "[id: " << dfs[i].id << ", speed: " << dfs[i].speed << "]";
		if (i != nummOfElem - 1) cout << "->";
	}
	cout << endl;
}

void GraphVisit::minTravelTime(int startId, int endId) {
	// Provera da li senzori postoje
	if (!sensors.sensorExists(startId) || !sensors.sensorExists(endId)) {
		std::cout << "Jedan od senzora ne postoji.\n";
		return;
	}

	resetVisits();

	//2000 je aproksimacija najvece tezine po grani  
	double INF = nummOfSensors * 2000.0;

	double* distance = new double[nummOfSensors];
	int* prev = new int[nummOfSensors];

	//Inicijalizacija
	for (int i = 0; i < nummOfSensors; i++) {
		distance[i] = INF;
		prev[i] = -1;
	}

	
	int startIndex = -1;
	int endIndex = -1;
	for (int i = 0; i < nummOfSensors; i++) {
		if (sensors.getSensor(i).id == startId) startIndex = i;
		else if (sensors.getSensor(i).id == endId) endIndex = i;
	}

	if (startIndex == -1 || endIndex == -1) {
		cout << "Senzori nisu validni! " << endl;
		delete[] distance;
		delete[] prev;
		return;
	}

	distance[startIndex] = 0;

	//Dijkstra algoritam
	for (int i = 0; i < nummOfSensors; i++) {
		double minDist = INF;
		int u = -1;

		// nalazimo neposecen cvor sa najmanjom distancom
		for (int j = 0; j < nummOfSensors; j++) {
			if (!visits[j].visited && distance[j] < minDist) {
				minDist = distance[j];
				u = j;
			}
		}

		if (u == -1) break; //nema vise dostupnih cvorova

		visits[u].visited = true;
		int uId = visits[u].sensorId;

		int start = indices.getSensorStartIndex(uId);
		int finish = indices.getNextEdgeIndex(uId);

		//Prolazimo sve susede naseg cvora
		for (int j = start; j < finish; j++) {
			int vId = edges.getIdAtIndex(j);
			if (vId == -1) continue;

			int v = -1;
			for (int k = 0; k < nummOfSensors; k++) {
				if (visits[k].sensorId == vId) {
					v = k;
					break;
				}
			}

			if (v == -1 || visits[v].visited) continue;

			double time = edges.getWeight(j)->weight;

			if (distance[u] + time < distance[v]) {
				distance[v] = distance[u] + time;
				prev[v] = u;
			}
		}
	}


	//Ispis puta
	if (distance[endIndex] == INF) {
		cout << "Ne postoji putanja izmedju senzora! " << endl;
	}
	else {
		// Sakupljanje putanje unazad (od kraja ka pocetku)
		int* path = new int[nummOfSensors];
		int pathLength = 0;

		int curr = endIndex;
		while (curr != -1) {
			path[pathLength++] = visits[curr].sensorId;
			curr = prev[curr];
		}

		// Ispis putanje (od pocetka ka kraju)
		cout << "Putanja: ";
		for (int i = pathLength - 1; i >= 0; i--) {
			cout << path[i];
			if (i != 0) std::cout << " -> ";
		}

		// Ispis ukupnog vremena
		cout << "\nUkupno vreme: " << distance[endIndex] << " ms\n";

		delete[] path;
	}
	delete[] distance;
	delete[] prev;

}

void GraphVisit::eccentricity() {
	// Provera da li imamo senzore
	if (nummOfSensors == 0) {
		cout << "Ne postoje senzori! " << endl;
		return;
	}

	// Ekscentricnost svakog senzora
	double* eccentricities = new double[nummOfSensors];

	for (int s = 0; s < nummOfSensors; s++) {
		resetVisits();

		//2000 je aproksimacija najvece tezine po grani
		double INF = nummOfSensors * 2000.0;
		double* distance = new double[nummOfSensors];
		int* prev = new int[nummOfSensors];

		for (int i = 0; i < nummOfSensors; i++) {
			distance[i] = INF;
			prev[i] = -1;
		}

		distance[s] = 0;

		// Dijkstra
		for (int i = 0; i < nummOfSensors; i++) {
			double minDist = INF;
			int u = -1;

			for (int j = 0; j < nummOfSensors; j++) {
				if (!visits[j].visited && distance[j] < minDist) {
					minDist = distance[j];
					u = j;
				}
			}

			if (u == -1) break;
			visits[u].visited = true;
			int uId = visits[u].sensorId;

			int start = indices.getSensorStartIndex(uId);
			int finish = indices.getNextEdgeIndex(uId);

			for (int j = start; j < finish; j++) {
				int vId = edges.getIdAtIndex(j);
				if (vId == -1) continue;

				int v = -1;
				for (int k = 0; k < nummOfSensors; k++) {
					if (visits[k].sensorId == vId) {
						v = k;
						break;
					}
				}

				if (v == -1 || visits[v].visited) continue;

				double time = edges.getWeight(j)->weight;

				if (distance[u] + time < distance[v]) {
					distance[v] = distance[u] + time;
					prev[v] = u;
				}
			}
		}

		// Ekscentricnost = maksimalna distanca od ovog senzora
		double maxDistance = 0;
		for (int i = 0; i < nummOfSensors; i++) {
			if (distance[i] != INF && distance[i] > maxDistance) {
				maxDistance = distance[i];
			}
		}

		eccentricities[s] = maxDistance;

		delete[] distance;
		delete[] prev;
	}

	// Trazimo centralni senzor
	double minEcc = eccentricities[0];
	int centralIndex = 0;
	for (int i = 1; i < nummOfSensors; i++) {
		if (eccentricities[i] < minEcc) {
			minEcc = eccentricities[i];
			centralIndex = i;
		}
	}

	// Ispis rezultata
	std::cout << "Ekscentriciteti senzora:\n";
	for (int i = 0; i < nummOfSensors; i++) {
		std::cout << "Senzor " << visits[i].sensorId << ": " << eccentricities[i] << " ms\n";
	}

	std::cout << "Centralni senzor: " << visits[centralIndex].sensorId
		<< " sa ekscentricitetom " << eccentricities[centralIndex] << " ms\n";

	delete[] eccentricities;
}





