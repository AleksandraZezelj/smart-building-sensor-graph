#pragma once
#include "List.h"

struct Edges {
	int id; // id od cvora ka kome postoji grana od cvora datog indeksa
	double weight;
	double distance; //da li mi treba
	int index;
	Edges* next;
};

class edgesList {
public:
	edgesList();

	void push(int id, double weight, double distance, int index);
	void addToEdges(int newId, double weight, double distance, int index);

	void removeOutgoingEdges(int start, int finish);
	int removeIncomingEdges(int sensorId);
	void printEdges();
	void freeEdges();

	Edges* getWeight(int index);

	int getIdAtIndex(int indexInEdges);
	void sortSegment(int start, int finish);

private:
	Edges* head;
	Edges* tail;

};


