#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "AlgorithmTester.h"
#include "UserInterface.h"


int main()
{
	// Set up the random number generator
	srand(time(0));

	AlgorithmTester algorithmTester;
	UserInterface userInterface(&algorithmTester);

	userInterface.beginSession();
}