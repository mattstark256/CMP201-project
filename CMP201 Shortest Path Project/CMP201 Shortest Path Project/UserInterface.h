#pragma once

#include "AlgorithmTester.h"


// UserInterface contains menus allowing the user to interact with the application. It handles input then calls funtions in algorithmTester.


class UserInterface
{
public:
	UserInterface(AlgorithmTester* _algorithmTester);
	~UserInterface();

	void beginSession();

private:
	AlgorithmTester* algorithmTester;

	void mainMenu();
	void visualizeAlgorithm();
	void benchmarkAlgorithms();

	int getIntInput(int min, int max);
	Algorithm selectAlgorithm();
};

