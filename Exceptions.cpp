//Eceptions.cpp

#include "Exceptions.h"
#include <sstream>
using namespace std;

GraphExceptions::GraphExceptions(){}

string SensorNotFoundExceptions::getMessage() const {
	stringstream ss;
	ss << "Senzor nije pronadjen. ";
	return ss.str();
}

string SensorAlreadyExists::getMessage() const {
	stringstream ss;
	ss << "Senzor sa tim id-jem vec postoji. ";
	return ss.str();
}

string SensorIdIsNegative::getMessage() const {
	stringstream ss;
	ss << "Id senzora mora biti pozitivan ceo broj. ";
	return ss.str();
}

string Exception::getMessage() const {
	stringstream ss;
	ss << "Doslo je do greske! ";
	return ss.str();

}

