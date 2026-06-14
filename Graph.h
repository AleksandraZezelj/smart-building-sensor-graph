#pragma once
#include "LKG.h"
#include "List.h"
#include "Edges.h"
#include "Indices.h"

using namespace std;


class Graph {
public:

	Graph(int nummOfSensors, unsigned long seed, double p);

	~Graph();

	void graphCreate();

	void printMatrix();

	void addSensorToGraph(int sensorId);

	void removeSensor(int sensorId);

	void printGraph();

	const List& getSensors() const;

	const indicesList& getIndices() const;

	const edgesList& getEdges() const;

	const int& getNummOfSensors() const;

private:
	int nummOfSensors;
	unsigned long seed;
	double p;

	LKG generator;
	List sensors;
	edgesList edges;
	indicesList indices;

	void addSensors();
	bool branchExists();
	double branchWeight(Sensor firstSensor, Sensor secondSensor, double distance);
	double min(double a, double b);


};

