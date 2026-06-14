#include "List.h"
#include <iostream>

List::List()
	:head(nullptr),
	tail(nullptr),
	index(0)
{}

void List::push(int id, int speed) {
	Sensor* node = new Sensor;
	node->id = id;
	node->speed = speed;
	node->next = nullptr;
	node->index = index;

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

void List::remove(int id) {
	Sensor* curr = head;
	Sensor* prev = nullptr;

	while (curr != nullptr) {
		if (curr->id == id) {

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

			//korigujemo indekse
			Sensor* tmp;
			if (prev == nullptr) tmp = head;
			else tmp = prev->next;
			while (tmp) {
				tmp->index--;
				tmp = tmp->next;
			}

			curr->next = nullptr;
			index--;
			delete curr;

			return;

		}
		prev = curr;
		curr = curr->next;
	}
	
}

void List::printList() {
	Sensor* curr = head;

	while (curr != nullptr) {
		std::cout << "(" << curr->id << ", " << curr->speed << ")";
		curr = curr->next;
	}
	std::cout << "\n";
}

void List::freeList() {
	Sensor* curr = head;

	while (curr != nullptr) {
		Sensor* tmp = curr;
		curr = curr->next;
		delete tmp;
	}
	head = nullptr;
	tail = nullptr;
}


Sensor List::getSensor(int index) {
	Sensor* curr = head;

	while (curr != nullptr) {
		if (curr->index == index) return *curr;
		curr = curr->next;
	}

	Sensor error;
	error.id = -1;
	error.speed = -1;
	error.next = nullptr;
	return error;
}

Sensor List::getSensorWithId(int sensorId) {
	Sensor* curr = head;

	while (curr != nullptr) {
		if (curr->id == sensorId) return *curr;
		curr = curr->next;
	}

	Sensor error;
	error.id = -1;
	error.speed = -1;
	error.next = nullptr;
	return error;
}



bool List::sensorExists(int id) {
	Sensor* curr = head;

	while (curr) {
		if (curr->id == id) return true;

		curr = curr->next;
	}

	return false;
}



