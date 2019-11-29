#pragma once

#include "AStarNode.h"
#include <vector>


class AStarOpenList
{
public:
	AStarOpenList();
	~AStarOpenList();

	void deleteNode(std::vector<AStarNode*>::iterator it);

	// I'm using the back for the lowest f values. This is because with vectors, adding and removing elements requires moving every element after the modified element
	AStarNode* getBackNode();
	void popBack();

	void insertOrdered(AStarNode* node);

	// Search for an element and return the index. Returns -1 if it's not found.
	// The reason I'm doing it this way is so I only need to search the list once when I check a node then delete it from the list afterwards.
	std::vector<AStarNode*>::iterator findNode(Vector2i coord);
	// This is used to check whether findNode found anything. findNode returns list.end() if it didn't find anything. 
	bool iteratorIsEnd(std::vector<AStarNode*>::iterator it);

	void deleteAll();

	bool isEmpty();

private:
	std::vector<AStarNode*> list;
};

