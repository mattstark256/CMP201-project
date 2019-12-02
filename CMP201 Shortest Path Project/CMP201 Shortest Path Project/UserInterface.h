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
	void testAlgorithmPerformance();
	void testAlgorithmPerformanceHeadToHead();
	void testAlgorithmPerformanceVsMapSize();
	void testAlgorithmPerformanceVsMapSizeHeadToHead();

	int getIntInput();
	Algorithm selectAlgorithm();
	void printAlgorithmName(Algorithm algorithm);
};

