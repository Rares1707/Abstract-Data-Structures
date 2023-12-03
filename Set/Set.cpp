#include "Set.h"
#include "SetITerator.h"

void Set::resize(int newLowerBound, int newUpperBound)
{
	if (this->currentNumberOfElements == 1 && newLowerBound == 0 && newUpperBound == 0) 
	{
		this->lowerBound = this->upperBound = 0;
		delete[] this->elements;
		return;
	}

	int newCapacity = newUpperBound - newLowerBound + 1;
	TElem* newElements = new TElem[newCapacity];

	if (this->currentNumberOfElements == 0)
	{
		this->lowerBound = newLowerBound;
		this->upperBound = newLowerBound;
		this->elements = newElements;
		return;
	}

	if (newUpperBound < this->upperBound)
	{
		for (int i = 0; i < newCapacity; i++)
		{
			newElements[i] = this->elements[i];
		}
		delete[] this->elements;
		this->upperBound = newUpperBound;
		this->elements = newElements;
		return;
	}

	if (newUpperBound > this->upperBound)
	{
		int oldCapacity = this->upperBound - this->lowerBound + 1;
		for (int i = 0; i < oldCapacity; i++)
		{
			newElements[i] = this->elements[i];
		}
		for (int i = oldCapacity; i < newCapacity; i++)
		{
			newElements[i] = false;
		}
		delete[] this->elements;
		this->upperBound = newUpperBound;
		this->elements = newElements;
		return;
	}

	if (newLowerBound < this->lowerBound)
	{
		int offsetOfElementsInNewArray = this->lowerBound - newLowerBound;
		int oldCapacity = this->upperBound - this->lowerBound + 1;

		for (int i = 0; i < newCapacity; i++)
		{
			newElements[i] = false;
		}

		if (offsetOfElementsInNewArray >= 0)
		{
			for (int i = 0; i < oldCapacity; i++)
			{
				newElements[i + offsetOfElementsInNewArray] = this->elements[i];
			}
		}
		else if (offsetOfElementsInNewArray < 0)
		{
			for (int i = -offsetOfElementsInNewArray; i < oldCapacity; i++)
			{
				newElements[i + offsetOfElementsInNewArray] = this->elements[i];
			}
		}
		delete[] this->elements;
		this->lowerBound = newLowerBound;
		this->elements = newElements;
		return;
	}

	if (newLowerBound > this->lowerBound)
	{
		int offsetOfElementsInNewArray = this->lowerBound - newLowerBound;
		if (offsetOfElementsInNewArray < 0)
		{
			offsetOfElementsInNewArray *= -1;
		}
		int oldCapacity = this->upperBound - this->lowerBound + 1;
		for (int i = 0; i < newCapacity; i++)
		{
			newElements[i] = this->elements[i + offsetOfElementsInNewArray];
		}
		delete[] this->elements;
		this->lowerBound = newLowerBound;
		this->elements = newElements;
		return;
	}
}
//Best case: Theta(1), Worst case: Theta(newCapacity), Total complexity: O(newCapacity)


Set::Set() {
	this->lowerBound = 0;
	this->upperBound = 0;
	this->currentNumberOfElements = 0;
}
//Theta(1)

bool Set::add(TElem elem) { 
	if (elem >= this->lowerBound && elem <= this->upperBound && this->currentNumberOfElements > 0)
	{
		if (this->elements[elem - lowerBound] == false)
		{
			this->elements[elem - lowerBound] = true;
			currentNumberOfElements++;
			return true;
		}
		else
		{
			return false;
		}
	}
	if (this->currentNumberOfElements == 0) 
	{
		resize(elem, elem);
		this->elements[0] = true;
		currentNumberOfElements++;
		return true;
	}
	if (elem < this->lowerBound)
	{
		resize(elem, this->upperBound);
		this->elements[0] = true;
		currentNumberOfElements++;
		return true;
	}
	if (elem > this->upperBound)
	{
		resize(this->lowerBound, elem);
		this->elements[elem - lowerBound] = true;
		currentNumberOfElements++;
		return true;
	}
}
//Best case: Theta(1), Worst case: Theta(newUpperBound - newLowerBound) 
//=> Total complexity O(newUpperBound - newLowerBound)


bool Set::remove(TElem elem) {
	if (this->search(elem) == false)
	{
		return false;
	}
	if (this->currentNumberOfElements == 0)
	{
		return false;
	}
	if (this->currentNumberOfElements == 1 && this->lowerBound == elem)
	{
		resize(0, 0);
		this->currentNumberOfElements = 0;
		return true;
	}
	if (elem > this->lowerBound && elem < this->upperBound && this->elements[elem - lowerBound])
	{
		if (this->elements[elem - lowerBound] == true)
		{
			this->elements[elem - lowerBound] = false;
			this->currentNumberOfElements--;
			return true;
		}
		else if (this->elements[elem - lowerBound] == false)
		{
			return false;
		}
	}
	if (elem == this->lowerBound)
	{
		int i, capacity = this->upperBound - this->lowerBound + 1;
		for (i = 1; i < capacity; i++)
		{
			if (this->elements[i])
				break;
		}
		resize(this->lowerBound + i, this->upperBound);
		this->currentNumberOfElements--;
		return true;
	}
	if (elem == this->upperBound)
	{
		int i, capacity = this->upperBound - this->lowerBound + 1;
		int c = 0;
		for (i = capacity - 2; i >= 0; i--)
		{
			c++;
			if (this->elements[i])
				break;
		}
		resize(this->lowerBound, this->upperBound - c);
		this->currentNumberOfElements--;
		return true;
	}
	return false;
}
//Best case: Theta(1), Worst case: Theta(oldCapacity) => Total complexity: O(oldCapacity)


bool Set::search(TElem elem) const {
	if (this->currentNumberOfElements == 0)
	{
		return false;
	}
	if (elem <= this->upperBound && elem >= this->lowerBound)
		return this->elements[elem - this->lowerBound];
	return false;
}
//Theta(1)

int Set::size() const {
	return this->currentNumberOfElements;
}
//Theta(1)


bool Set::isEmpty() const {
	if (this->currentNumberOfElements == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//Theta(1)


Set::~Set() {
	if (this->currentNumberOfElements > 0)
		delete[] this->elements;
}
//Theta(1)

SetIterator Set::iterator() const {
	return SetIterator(*this);
}

void Set::empty()
{
	lowerBound = upperBound = currentNumberOfElements = 0;
	delete[] elements;
}
//Theta(1)

