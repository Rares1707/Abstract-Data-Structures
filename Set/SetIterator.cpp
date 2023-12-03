#include "SetIterator.h"
#include "Set.h"
#include <exception>
using namespace std;


SetIterator::SetIterator(const Set& m) : set(m)
{
	this->positionOfCurrentElement = -1;
	if (this->set.currentNumberOfElements != 0)
	{
		this->positionOfCurrentElement = 0;
	}
}
//Theta(1)


void SetIterator::first() {
	this->positionOfCurrentElement = 0;
}
//Theta(1)


void SetIterator::next() {
	if (this->valid() == false)
	{
		throw exception();
	}
	for (int i = this->positionOfCurrentElement + 1; i < this->set.upperBound - this->set.lowerBound + 1; i++)
	{
		if (this->set.elements[i])
		{
			this->positionOfCurrentElement = i;
			return;
		}
	}
	this->positionOfCurrentElement = this->set.upperBound - this->set.lowerBound + 1; //for clarity
}
//Best case: Theta(1), Worst case: Theta(upperBound - lowerBound) => Total complexity O(upperBound - lowerBound)


TElem SetIterator::getCurrent()
{
	if (this->valid() == false)
	{
		throw exception();
	}
	return this->positionOfCurrentElement + this->set.lowerBound;
}
//Theta(1)


bool SetIterator::valid() const {
	if (this->set.currentNumberOfElements == 0)
	{
		return false;
	}
	if (this->positionOfCurrentElement == this->set.upperBound - this->set.lowerBound + 1)
	{
		return false;
	}
	if (this->positionOfCurrentElement == -1)
	{
		return false;
	}
	return true;
}
//Theta(1)



