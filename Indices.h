#pragma once

struct Indices {
	int indexForEdges;
	int index;
	int id;
	Indices* next;
};

class indicesList {
public:
	indicesList();

	void push(int indexForEdges, int index);
	void printIndices();
	void freeIndices();
	int getInxForEdges(int index);
	int getNextEdgeIndex(int id);
	int getLastEdgeInx();
	int getSensorStartIndex(int sensorId);
	void incIndices(int newId);
	void removeSensorIndex(int sensorId);
	void decrementIndicesAfter(int index);

private:
	Indices* head;
	Indices* tail;
	int index;
	
};



