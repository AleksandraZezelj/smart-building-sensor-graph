#pragma once


struct Sensor {
	int id;
	int speed;
	int index;
	Sensor* next;
};

class List {
public:
	List();

	void push (int id, int speed);
	void remove(int id);
	void printList();
	void freeList();
	Sensor getSensor(int index);
	Sensor getSensorWithId(int sensorId);
	bool sensorExists(int id);

private:
	Sensor* head;
	Sensor* tail;
	int index;

};

