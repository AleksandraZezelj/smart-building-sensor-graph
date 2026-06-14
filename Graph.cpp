#include "Graph.h"
#include "Exceptions.h"
#include <iostream>

Graph::Graph(int nummOfSensors, unsigned long seed, double p)
	:generator(seed),
	nummOfSensors(nummOfSensors),
	p(p),
	seed(seed)
{}

Graph::~Graph() {
	edges.freeEdges();
	indices.freeIndices();
	sensors.freeList();
}


void Graph::addSensors() {
	for(int i = 0; i < nummOfSensors; i++){


		int id = i;
		int speed = generator.randomInRange(1, 100);

	    sensors.push(id, speed);
		
	}
}

bool Graph::branchExists() {
	double u = generator.randomDouble();

	if (u < p) return true;
	else return false;
}

double Graph::branchWeight(Sensor firstSensor, Sensor secondSensor, double distance) {
	double weight = distance + 100 - min(firstSensor.speed, secondSensor.speed);
	return weight;
}

double Graph::min(double a, double b) {
	if (a > b) return b;
	else return a;
}

void Graph::graphCreate() {
	addSensors();
	int indexIndices = 0;
	int indexEdges = 0;
	for (int i = 0; i < nummOfSensors; i++) {

		//jednom na pocetku kreiramo graf i onda znamo da id-jevi idu redom kao i 
		indices.push(indexIndices, i);
		Sensor firstSensor = sensors.getSensor(i);

		for (int j = 0; j < nummOfSensors; j++) {

			if (i != j && branchExists()) {
				Sensor secondSensor = sensors.getSensor(j);

				double distance = generator.randomForDistance();
				double weight = branchWeight(firstSensor, secondSensor, distance);

				edges.push(secondSensor.id, weight, distance, indexEdges);
				indexIndices++;
				indexEdges++;
			}
		}
	}
	indices.push(indexIndices, nummOfSensors); //do kog indeksa ide poslednji
}

void Graph::printMatrix() {

	cout << "     ";
	for (int j = 0; j < nummOfSensors; j++) {
		cout << sensors.getSensor(j).id << "   ";
	}
	cout << "\n";

	for (int j = 0; j < nummOfSensors; j++) {
		cout  << " ____";
	}
	cout << "\n";

	//za svaki red
	for (int i = 0; i < nummOfSensors; i++) {
		Sensor from = sensors.getSensor(i);
		cout << from.id << " | "; // Id senzora za red

		int start = indices.getInxForEdges(i);
		int finish = i + 1 < nummOfSensors ? indices.getInxForEdges(i + 1) : indices.getLastEdgeInx();
		
		//za svaku kolonu
		for (int j = 0; j < nummOfSensors; j++) {
			Sensor to = sensors.getSensor(j); // senzor za kolonu
			double weight = 0; //default ako nema grane

			
			// trazimo granu u edge listi
			for (int k = start; k < finish; k++) {
				Edges* e = edges.getWeight(k);
				if (e && e->id == to.id) {
					weight = e->weight;
					break;
				}
			}
			
			cout << weight << "     ";
		}

		cout << "\n";
		for (int j = 0; j < nummOfSensors; j++) {
			cout << " ____";
		}
		cout << "\n";
	}
	
}


void Graph::addSensorToGraph(int sensorId) {
	// Proveravamo da li sensor vec postoji
	if (sensors.sensorExists(sensorId)) throw SensorAlreadyExists();

	// Proveravamo da li je id senzora pozitivan broj
	if (sensorId < 0) throw SensorIdIsNegative();

	// Kreiramo novi sensor sa datim ID-jem i random speed-om
	Sensor sensor;
	sensor.id = sensorId;
	double speed = generator.randomInRange(1, 100);
	sensor.speed = speed;

	// Dodajemo sensor u listu i povecavamo broj senzora
	sensors.push(sensorId, speed);
	nummOfSensors++;

	// Dodajemo novi zapis u indices listu za novi senzor.
	// getLastEdgeInx() predstavlja krajnji indeks u edges listi
	// za grane koje polaze iz poslednjeg senzora.
	indices.push(indices.getLastEdgeInx(), sensor.id);

	//smer od starog senzora ka novom
	//uzimamo sve senzore osim sad dodatog
	for (int i = 0; i < nummOfSensors-1; i++) {
		Sensor old = sensors.getSensor(i);
		
		if (branchExists()){

			double distance = generator.randomForDistance();
			double weight = branchWeight(sensor, old, distance);
			
			int inxForEdges = indices.getNextEdgeIndex(old.id);
			
			//ide pre povecavanja indeksa u indices listi
			edges.addToEdges(sensor.id, weight, distance, inxForEdges);

			// Pomera sve indekse za edge-ove koji dolaze posle trenutnog
			// Kako bi se ocuvala ispravna linearizovana lista
			indices.incIndices(old.id);
		}
	}

	//smer od novog senzora ka starom
	//uzimamo sve senzore osim sad dodatog
	for (int i = 0; i < nummOfSensors-1; i++) {
		Sensor old = sensors.getSensor(i);
		
		if (branchExists()) {
			double distance = generator.randomForDistance();
			double weight = branchWeight(sensor, old, distance);

			//ide pre povecavanja indeksa u indices listi
			edges.addToEdges(sensor.id, weight, distance, indices.getLastEdgeInx());

		}
	}

	}

void Graph::removeSensor(int sensorId) {

	int start = indices.getSensorStartIndex(sensorId);
	int finish = indices.getNextEdgeIndex(sensorId);

	// ako je poslednji senzor
	if (finish == -1) {
		finish = indices.getLastEdgeInx();
	}

	// brisemo grane koje idu od senzora koji brisemo
	edges.removeOutgoingEdges(start, finish);

	// Brisemo sve grane koje pokazuju na sensor koji brisemo
	int index;
	//Dokle god postoji grana ka cvoru koji brisemo uklanjamo je i korigujemo indekse
	while ((index = edges.removeIncomingEdges(sensorId)) != -1) {
		indices.decrementIndicesAfter(index);
	}

	// brisemo indekse grana koje idu od sensora koji brisemo
	indices.removeSensorIndex(sensorId);
	

	//brisemo senzor
	sensors.remove(sensorId);
	nummOfSensors--;

}

void Graph::printGraph() {
	for (int i = 0; i < nummOfSensors; i++) {
		cout << "Sensor id = " << sensors.getSensor(i).id << ": ";

		int start = indices.getSensorStartIndex(sensors.getSensor(i).id);
		int finish = indices.getNextEdgeIndex(sensors.getSensor(i).id);

		for (int j = start; j < finish; j++) {
			Edges* e = edges.getWeight(j);
			if(e) cout << "->" << e->id << " (" << e->weight << ") ";
		}

		cout << endl;
	}
}

const List& Graph::getSensors() const {
	return sensors;
}

const indicesList& Graph::getIndices() const {
	return indices;
}

const edgesList& Graph::getEdges() const {
	return edges;
}

const int& Graph::getNummOfSensors() const{
	return nummOfSensors;
}




