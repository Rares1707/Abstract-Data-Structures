#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	currentNode = m.head; 
}
//Theta(1)

void SortedSetIterator::first() {
	currentNode = multime.head;
}
//Theta(1)


void SortedSetIterator::next() {
	if (this->valid() == false)
	{
		throw exception();
	}
	currentNode = currentNode->next;
}
//Theta(1)

TElem SortedSetIterator::getCurrent()
{
	if (this->valid() == false)
	{
		throw exception();
	}
	return currentNode->element;
}
//Theta(1)

bool SortedSetIterator::valid() const {
	if (currentNode == nullptr)
		return false;
	return true;
}
//Theta(1)

void SortedSetIterator::jumpForward(int k)
{
	if (this->valid() == false || k <= 0)
	{
		throw exception();
	}

	while (k && this->valid())
	{
		this->next();
		k--;
	}
}
//Best case: Theta(1), Worst case: Theta(k) => Total Complexity: O(k)

