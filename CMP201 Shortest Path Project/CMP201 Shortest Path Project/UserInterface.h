#pragma once

#include "AlgorithmTester.h"

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
	int getIntInput();
	Algorithm selectAlgorithm();
};

