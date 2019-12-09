#pragma once

#include "DijkstraNode.h"
#include <vector>


// The open set used by DijkstraPathfinder


class DijkstraOpenSet
{
public:
	DijkstraOpenSet();
	~DijkstraOpenSet();

	bool isEmpty();
	void deleteNode(std::vector<DijkstraNode*>::iterator it);
	void deleteAll();

	// I'm using the back for the lowest cost values. This is because with vectors, adding and removing elements requires moving every element after the modified element
	DijkstraNode* getBackNode();
	void popBack();
	void insertOrdered(DijkstraNode* node);

	// Search for an element and return the index. Returns set.end() if it's not found. The reason I'm doing it this way is so I only need to search the set once when I check a node then delete it from the set afterwards.
	std::vector<DijkstraNode*>::iterator findNode(Vector2i coord);
	// This is used to check whether findNode found anything. 
	bool isEnd(std::vector<DijkstraNode*>::iterator it);

	// Used for displaying the set
	const std::vector<DijkstraNode*>* getSet() const;

private:
	std::vector<DijkstraNode*> set;
};