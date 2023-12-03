#pragma once
#include "SortedIndexedList.h"
#include <stack>

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	//Representation
    std::stack<PointerToNode> auxiliaryStack; //check to see if it is empty

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};


