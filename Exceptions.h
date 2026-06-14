//Exceptions.h

#pragma once
#include <string>

class GraphExceptions {
public:
	GraphExceptions();

	virtual std::string getMessage() const = 0;
private:

};

class SensorNotFoundExceptions : public GraphExceptions {
public:
	virtual std::string getMessage() const;

};

class SensorAlreadyExists : public GraphExceptions {
public:
	virtual std::string getMessage() const;

};

class SensorIdIsNegative : public GraphExceptions {
public:
	virtual std::string getMessage() const;
};

class Exception : public GraphExceptions {
public:
	virtual std::string getMessage() const;
};

