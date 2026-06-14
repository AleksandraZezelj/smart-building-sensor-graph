#include "LKG.h"

LKG::LKG(unsigned long seed)
	:seed(seed)
{}

unsigned long LKG::random() {
	seed = 429493445 * seed + 907633385;
	return seed;
}

unsigned long LKG::randomInt() {
	return random();
}

double LKG::randomDouble() {
	return random() / 4294967296.0;
}

int LKG::randomInRange(int a, int b) {
	return a + (random() % (b - a + 1));
}

double LKG::randomForDistance() {
	int d = randomInRange(5, 300);
	return d / 10.0;
}


