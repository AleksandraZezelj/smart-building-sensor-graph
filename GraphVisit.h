#pragma once
#include "Graph.h"
#include "Indices.h"
#include "Edges.h"
#include "List.h"

struct Visit {
	int sensorId;
	int index;
	bool visited = false;
};

class GraphVisit {
public:
	GraphVisit(const Graph& graph);
	~GraphVisit();

	void visit(int visitType, int startId);

	void minTravelTime(int startId, int endId);

	void eccentricity();

private:
	void BFS(int startId); //VisitType 1
	void DFS(int startId); //VisitType 2

	void printBFS(int nummOfElem);
	void printDFS(int nummOfElem);

	const Graph& graph;
	int nummOfSensors;
	indicesList indices;
	edgesList edges;
    List sensors;

	Visit* visits;
	void resetVisits();

	Sensor* bfs;
	Sensor* dfs;
	Sensor* path;

};