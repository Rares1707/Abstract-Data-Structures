#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


SortedMultiMap::SortedMultiMap(Relation r) {
	relation = r;
	currentNumberOfPairs = 0;
	head = tail = -1;

	//allocate space for the vectors
	const int initialCapacity = 10;

	maximumCapacity = initialCapacity;
	elements = new TElem[initialCapacity];
	nextElementPosition = new int[initialCapacity];
	previousElementPosition = new int[initialCapacity];

	for (int i = 0; i < initialCapacity; i++)
	{
		nextElementPosition[i] = i + 1;
		//previousElementPosition[i] = i - 1;
	}
	nextElementPosition[initialCapacity - 1] = -1;
	firstFreeElementPosition = 0;
}
//Theta(initialCapacity)

void SortedMultiMap::resize()
{
	//note: we only resize the map when we need more space

	const int resizeFactor = 2;
	const int newCapacity = maximumCapacity * resizeFactor;

	TElem* newElements = new TElem[newCapacity];
	int* newNextElementPosition = new int[newCapacity];
	int* newPreviousElementPosition = new int[newCapacity];

	for (int i = 0; i < maximumCapacity; i++)
	{
		newElements[i] = elements[i];
		newNextElementPosition[i] = nextElementPosition[i];
		newPreviousElementPosition[i] = previousElementPosition[i];
	}

	//newNextElementPosition[tail] = maximumCapacity;
	//newPreviousElementPosition[maximumCapacity] = tail;
	//newNextElementPosition[maximumCapacity] = maximumCapacity + 1;

	for (int i = maximumCapacity; i < newCapacity; i++)
	{
		newNextElementPosition[i] = i + 1;
		//newPreviousElementPosition[i] = i - 1;
	}
	newNextElementPosition[newCapacity - 1] = -1;

	firstFreeElementPosition = maximumCapacity;
	maximumCapacity = newCapacity;

	delete[] elements;
	delete[] nextElementPosition;
	delete[] previousElementPosition;
	elements = newElements;
	nextElementPosition = newNextElementPosition;
	previousElementPosition = newPreviousElementPosition;
}
//Theta(newCapacity);

int SortedMultiMap::allocateSpaceForAnElement()
{
	if (firstFreeElementPosition == -1)
	{
		resize();
	}
	int newFreePosition = firstFreeElementPosition;
	firstFreeElementPosition = nextElementPosition[firstFreeElementPosition];
	return newFreePosition;
}
//Best case: Theta(1), Worst case: Theta(newCapacity) => Total complexity: O(newCapacity)

void SortedMultiMap::freePosition(int position)
{
	currentNumberOfPairs--;
	nextElementPosition[position] = firstFreeElementPosition;
	firstFreeElementPosition = position;
}
//Theta(1)

void SortedMultiMap::add(TKey c, TValue v) 
{
	int newPosition = allocateSpaceForAnElement();
	elements[newPosition].first = c;
	elements[newPosition].second = v;

	//Case 1: map is empty
	if (currentNumberOfPairs == 0) 
	{
		head = tail = newPosition;
		nextElementPosition[newPosition] = -1;
		previousElementPosition[newPosition] = -1;
		currentNumberOfPairs++;
		return;
	}

	//Case 2: map has one element
	if (currentNumberOfPairs == 1)
	{
		//Case 2.1: we insert it last
		if (relation(elements[head].first, c))
		{
			tail = newPosition;
		}
		else //Case 2.2: we insert it first
		{
			tail = head;
			head = newPosition;
		}
		nextElementPosition[head] = tail;
		nextElementPosition[tail] = -1;
		previousElementPosition[tail] = head;
		currentNumberOfPairs++;
		return;
	}

	currentNumberOfPairs++;
	//We already have at least two elements for the following cases
	int current = head;

	while (current != -1 && relation(elements[current].first, c))
	{
		current = nextElementPosition[current];
	}
	//Case 3: we insert it first
	if (current == head)
	{
		previousElementPosition[head] = newPosition;
		nextElementPosition[newPosition] = head;
		previousElementPosition[newPosition] = -1;
		head = newPosition;
		return;
	}
	//Case 4: we insert it last
	if (current == -1)
	{
		nextElementPosition[tail] = newPosition;
		previousElementPosition[newPosition] = tail;
		nextElementPosition[newPosition] = -1;
		tail = newPosition;
		return;
	}
	//Case 5: we insert it somewhere in the middle
	//here elements[current] > elements[newPosition]
	//so we must insert the new element between previous[current] and current
	previousElementPosition[newPosition] = previousElementPosition[current];
	nextElementPosition[newPosition] = current;
	
	nextElementPosition[previousElementPosition[current]] = newPosition;
	previousElementPosition[current] = newPosition;
}
//O(totalNumberOfElements)

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector <TValue> result = *(new vector<TValue>());
	int current = head;
	while (current != -1)
	{
		if (elements[current].first == c)
		{
			while (current != -1  && elements[current].first == c)
			{
				result.emplace_back(elements[current].second);
				current = nextElementPosition[current];
			}
			return result;
		}
		current = nextElementPosition[current];
	}
	return result;
}
//O(totalNumberOfElements)

bool SortedMultiMap::remove(TKey c, TValue v) {
	int current = head;
	int previousPosition = -1; //this variable is not actually needed, we can always use previousElementPosition[current] instead of it
	while (current != -1 && (elements[current].second != v || elements[current].first != c))
	{
		previousPosition = current; 
		current = nextElementPosition[current];
	}
	if (current != -1)
	{
		if (current == head && current == tail)
		{
			head = tail = -1;
		}
		else if (current == head)
		{
			head = nextElementPosition[head];
			previousElementPosition[head] = -1;
		}
		else if (current == tail)
		{
			tail = previousElementPosition[tail];
			nextElementPosition[tail] = -1;
		}
		else
		{
			nextElementPosition[previousPosition] = nextElementPosition[current];
			previousElementPosition[nextElementPosition[current]] = previousPosition;
		}
		freePosition(current);
		return true;
	}
	return false;
}
//O(totalNumberOfElements)

int SortedMultiMap::size() const {
	return currentNumberOfPairs;
}
//Theta(1)

bool SortedMultiMap::isEmpty() const {
	return currentNumberOfPairs == 0;
}
//Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

void SortedMultiMap::replace(TKey k, TValue oldValue, TValue newValue)
{
	int current = head;
	bool theKeyWasFound = false;
	while (current != -1)
	{
		if (elements[current].first == k)
		{
			theKeyWasFound = true;
		}
		if (elements[current].first == k && elements[current].second == oldValue)
		{
			elements[current].second = newValue;
		}
		else if (theKeyWasFound && elements[current].first != k)
		{
			break;
		}
		current = nextElementPosition[current];
	}
}
//O(n)

SortedMultiMap::~SortedMultiMap() {
	delete[] elements;
	delete[] nextElementPosition;
	delete[] previousElementPosition;
}
//Theta(1)