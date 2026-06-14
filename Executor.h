#pragma once
#include "Graph.h"
#include "GraphVisit.h"

using namespace std;

// Executor: glavna klasa koja izvrsava program
class Executor {
public:

	Executor();
	~Executor();

	void run();

private:

	int options();

	
	void addSensorToGraph(Graph &graph);
	void removeSensor(Graph &graph);
	void printMatrix(Graph &graph);
	void printGraph(Graph &graph);

	void visit1(GraphVisit& graphVisit);
	void visit2(GraphVisit& graphVisit);
	void minTravelTime(GraphVisit& graphVisit);
	void eccentricity(GraphVisit& graphVisit);

	
};