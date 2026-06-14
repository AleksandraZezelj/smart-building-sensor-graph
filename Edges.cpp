#include "Edges.h"
#include <iostream>

edgesList::edgesList()
	:head(nullptr),
	tail(nullptr)
{
}

void edgesList::push(int id, double weight, double distance, int index) {
	Edges* node = new Edges;
	node->id = id;
	node->weight = weight;
	node->distance = distance;
	node->index = index;
	node->next = nullptr;

	if (head == nullptr) {
		head = node;
		tail = node;
	}
	else {
		tail->next = node;
		tail = node;
	}

}

void edgesList::addToEdges(int newId, double weight, double distance, int index) {
	Edges* node = new Edges;
	node->id = newId;
	node->weight = weight;
	node->distance = distance;
	node->index = index;
	node->next = nullptr;

	//ako je lista prazna 
	if (head == nullptr) {
		head = tail = node;
		node->index = 0;
		return;
	}

	Edges* curr = head;
	Edges* prev = nullptr;

	while (curr && curr->index < index) {
		prev = curr;
		curr = curr->next;
	}

	//dodajemo na pocetak
	if (!prev) {
		node->next = head;
		head = node;
	}
	//dodajemo izmedju curr i prev
	else {
		prev->next = node;
		node->next = curr;
	}
	while (curr) {
		curr->index++;
		curr = curr->next;
	}
}


void edgesList::printEdges() {
	Edges* curr = head;

	while (curr != nullptr && curr->next != nullptr) {
		std::cout << "(" << curr->id << " - " << curr->next->id << ")";
		curr = curr->next;
	}
	std::cout << "\n";
}

void edgesList::freeEdges() {
	Edges* curr = head;

	while (curr != nullptr) {
		Edges* tmp = curr;
		curr = curr->next;
		delete tmp;
	}
	head = nullptr;
	tail = nullptr;
}

Edges* edgesList::getWeight(int index) {
	Edges* curr = head;

	while (curr != nullptr) {
		if (curr->index == index) return curr;
		curr = curr->next;
	}
	return curr;
}

void edgesList::removeOutgoingEdges(int start, int finish) {
	if (start >= finish) return;
	Edges* curr = head;
	Edges* prev = nullptr;

	//Pronalazimo prvi cvor koji se brise
	while (curr && curr->index < start) {
		prev = curr;
		curr = curr->next;
	}

	Edges* forDelete = curr;
	int counter = 0;

	while (curr && curr->index < finish) {
		curr = curr->next;
		counter++;
	}

	//curr je prvi posle obrisanih

	if (prev == nullptr) {
		head = curr;
	}

	else {
		prev->next = curr;
	}

	//ako smo brisali do kraja
	if (curr == nullptr) {
		tail = prev;
	}

	while (forDelete && counter) {
		Edges* tmp = forDelete;
		forDelete = forDelete->next;
		counter--;
		delete tmp;
	}
	
	//Korigovanje ostalih indeksa
	while (curr) {
		curr->index -= (finish - start);
		curr = curr->next;
	}

}

int edgesList::removeIncomingEdges(int sensorId) {
	Edges* curr = head;
	Edges* prev = nullptr;

	while (curr) {
		if(curr->id == sensorId){
			int deletedIndex = curr->index;

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
			delete curr;


			// Smanjujemo index za sve elemente posle obrisanog
			Edges* tmp;
			if (prev == nullptr) tmp = head;
			else tmp = prev->next;

			while (tmp != nullptr) {
				tmp->index--;
				tmp = tmp->next;
			}

			return deletedIndex;
	    }
	prev = curr;
	curr = curr->next;
    }
	return -1; //nema vise dolaznih grana
}

int edgesList::getIdAtIndex(int indexInEdges) {
	Edges* curr = head;
	Edges* prev = nullptr;

	while (curr != nullptr) {
		if (curr->index == indexInEdges) return curr->id;
		curr = curr->next;
	}
	return -1; //greska, ne postoji
}

void edgesList::sortSegment(int start, int finish) {
	if (start >= finish || !head) return;

	Edges* prevSegStart = nullptr;
	Edges* segStart = head;

	// Trazimo prethodni cvor segmenta
	while (segStart && segStart->index < start) {
		prevSegStart = segStart;
		segStart = segStart->next;
	}

	if (!segStart) return; // nista za sortirati

	// Trazimo kraj segmenta
	Edges* segEnd = segStart;
	while (segEnd && segEnd->index < finish - 1) {
		segEnd = segEnd->next;
	}

	Edges* afterSeg = segEnd ? segEnd->next : nullptr;
	if (segEnd) segEnd->next = nullptr; // odvajamo segment

	// Sortiraj segment po id 
	Edges* sorted = nullptr;
	Edges* curr = segStart;
	while (curr) {
		Edges* next = curr->next;
		if (!sorted || curr->id < sorted->id) {
			curr->next = sorted;
			sorted = curr;
		}
		else {
			Edges* s = sorted;
			while (s->next && s->next->id < curr->id) {
				s = s->next;
			}
			curr->next = s->next;
			s->next = curr;
		}
		curr = next;
	}

	// Spajamo segment nazad u listu
	if (prevSegStart) prevSegStart->next = sorted;
	else head = sorted;

	// Trazimo kraj segmenta da spojimo ostatak i azuriramo indekse
	Edges* tmp = sorted;
	int idx = start;
	while (tmp->next) {
		tmp->index = idx++;
		tmp = tmp->next;
	}
	tmp->index = idx++; // poslednji element segmenta

	tmp->next = afterSeg;

	// Update tail ako je segment bio na kraju
	if (!afterSeg) tail = tmp;
}


