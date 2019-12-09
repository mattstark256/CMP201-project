#pragma once

#include "AStarNode.h"
#include <vector>


// The open set used by AStarPathfinder


class AStarOpenSet
{
public:
	AStarOpenSet();
	~AStarOpenSet();

	bool isEmpty();
	void deleteNode(std::vector<AStarNode*>::iterator it);
	void deleteAll();

	// I'm using the back for the lowest f values. This is because with vectors, adding and removing elements requires moving every element after the modified element
	AStarNode* getBackNode();
	void popBack();
	void insertOrdered(AStarNode* node);

	// Search for an element and return the index. Returns set.end() if it's not found. The reason I'm doing it this way is so I only need to search the set once when I check a node then delete it from the set afterwards.
	std::vector<AStarNode*>::iterator findNode(Vector2i coord);
	// This is used to check whether findNode found anything. 
	bool isEnd(std::vector<AStarNode*>::iterator it);

	// Used for displaying the set
	const std::vector<AStarNode*>* getSet() const;

private:
	std::vector<AStarNode*> set;
};

