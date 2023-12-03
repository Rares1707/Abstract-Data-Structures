#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d)
{
	currentPosition = map.head;
}
//Theta(1)

void SMMIterator::first()
{
	currentPosition = map.head;
}
//Theta(1)

void SMMIterator::next()
{
	if (valid())
	{
		currentPosition = map.nextElementPosition[currentPosition];
	}
	else
	{
		throw exception();
	}
}
//Theta(1)

bool SMMIterator::valid() const
{
	return currentPosition != -1;
}
//Theta(1)

TElem SMMIterator::getCurrent() const
{
	if (valid())
	{
		return map.elements[currentPosition];
	}
	throw exception();
}
//Theta(1)


