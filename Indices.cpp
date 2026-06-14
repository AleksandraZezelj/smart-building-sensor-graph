#include "Indices.h"
#include <iostream>

indicesList::indicesList()
	:head(nullptr),
	tail(nullptr),
	index(0)
{}

void indicesList::push(int indexForEdges, int id) {
	Indices* node = new Indices;
	node->indexForEdges = indexForEdges;
	node->index = index;
	node->id = id;
	node->next = nullptr;

	if (head == nullptr) {
		head = node;
		tail = node;
	}
	else {
		tail->next = node;
		tail = node;
	}
	index++;
}

void indicesList::printIndices() {
	Indices* curr = head;

	while (curr != nullptr) {
		std::cout << curr->indexForEdges << ", ";
		curr = curr->next;
	}
	std::cout << "\n";
}

void indicesList::freeIndices() {
	Indices* curr = head;

	while (curr != nullptr) {
		Indices* tmp = curr;
		curr = curr->next;
		delete tmp;
	}
	head = nullptr;
	tail = nullptr;
}

int indicesList::getInxForEdges(int index) {
	Indices* curr = head;

	while (curr != nullptr) {
		if (curr->index == index) {
			return curr->indexForEdges;
		}
		curr = curr->next;
	}
	return -1; //greska
}

int indicesList::getNextEdgeIndex(int id) {
	Indices* curr = head;

	while (curr != nullptr) {
		if (curr->id == id) {
			if(curr->next) {
				curr = curr->next;
				return curr->indexForEdges;
			}
			else {
				return -1; //greska, nema sledeceg
			}
		}
		curr = curr->next;
	}
	return -1;//greska, senzor ne postoji
}

int indicesList::getLastEdgeInx() {
	return tail->indexForEdges;
}

int indicesList::getSensorStartIndex(int sensorId) {
	Indices* curr = head;

	while (curr != nullptr) {
		if (curr->id == sensorId) {
			return curr->indexForEdges;
		}
		curr = curr->next;
	}
	return -1;//greska
}

void indicesList::incIndices(int id) {
	Indices* curr = head;
	
	//nadji cvor sa datim id-jem
	while (curr && curr->id != id) {
		curr = curr->next;
	}

	if (curr) {
		//pocni od sledeceg cvora
		curr = curr->next;
		while (curr) {
			curr->indexForEdges++;
			curr = curr->next;
		}
			
	}
}

void indicesList::removeSensorIndex(int sensorId){
	Indices* curr = head;
	Indices* prev = nullptr;

	while (curr != nullptr) {
		if (curr->id == sensorId) {

			//brisemo prvi
			if (prev == nullptr) {
				head = curr->next;
			}

			//brisemo u sredini
			else {
				prev->next = curr->next;
			}

			//brisemo poslednji
			if (curr == tail) {
				tail = prev;
			}

			curr->next = nullptr;
			index--;
			delete curr;


			// Smanjujemo index za sve elemente posle obrisanog
			Indices* tmp;
			if (prev == nullptr) tmp = head;
			else tmp = prev->next;
		
			while (tmp != nullptr) {
				tmp->index--;
				tmp = tmp->next;
			}

			return;
		}
		prev = curr;
		curr = curr->next;
	}

}

void indicesList::decrementIndicesAfter(int index) {
	Indices* curr = head;

	while (curr != nullptr) {

		// Smanjujemo vrednost za sve elemente nakon index elementa
		if (curr->indexForEdges > index) {
			curr->indexForEdges--;
		}

		curr = curr->next;
	}
}
