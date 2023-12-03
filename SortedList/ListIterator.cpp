#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    first();
}

void ListIterator::first(){
    PointerToNode currentNode = list.root;
    while (!auxiliaryStack.empty())
    {
        auxiliaryStack.pop();
    }
    while (currentNode != nullptr)
    {
        auxiliaryStack.push(currentNode);
        currentNode = currentNode->left;
    }
}
//O(log height) which is O(n)

void ListIterator::next(){
    if (!valid())
    {
        throw exception();
    }
    PointerToNode currentNode = auxiliaryStack.top()->right;
    auxiliaryStack.pop();
    while (currentNode != nullptr)
    {
        auxiliaryStack.push(currentNode);
        currentNode = currentNode->left;
    }
}
//O(log height) which is O(n)

bool ListIterator::valid() const{
	return !auxiliaryStack.empty();
}
//Theta(1)

TComp ListIterator::getCurrent() const{
	if (!valid())
    {
        throw exception();
    }
	return auxiliaryStack.top()->element;
}
//Theta(1)

