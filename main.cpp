//main.cpp

#include "Executor.h"
#include "Exceptions.h"
#include <iostream>

int main() {
	try{
		Executor exe;
		exe.run();
	}
	catch (const SensorNotFoundExceptions e) {
		cout << e.getMessage() << endl;
	}
	catch (const SensorAlreadyExists e) {
		cout << e.getMessage() << endl;
	}
	catch (const Exception e) {
		cout << e.getMessage() << endl;
	}


	return 0;
}

