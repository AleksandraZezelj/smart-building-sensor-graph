#pragma once


class LKG {
public:
	LKG(unsigned long seed);

	
	unsigned long randomInt();
	double randomDouble();
	int randomInRange(int a, int b);
	double randomForDistance();
    
private:
	unsigned long random();
	unsigned long seed;
};


