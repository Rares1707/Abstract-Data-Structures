#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;


void Matrix::resizeAndRehash(int resizeFactor=2)
{
	int oldCapacity = capacity;
	divisorUsedForHashing = capacity = capacity * resizeFactor;

	elementOfHashtable* oldHashtable = hashtable;
	hashtable = new elementOfHashtable[capacity * resizeFactor];
	emptyHashtable();

	for (int i = 0; i < oldCapacity; i++)
	{
		if (oldHashtable[i].value != NULL_TELEM)
			insert(oldHashtable[i].line, oldHashtable[i].column, oldHashtable[i].value);
	}

	delete[] oldHashtable;
}
//Best case: Theta(capacity + currentNumberOfElements)
//Worst case: Theta(capacity + currentNumberOfElements^2) (impossible?)
//Total complexity: O(capacity + currentNumberOfElements^2)
//Note: the average case is MUCH better than the Total Complexity

void Matrix::emptyHashtable()
{
	for (int i = 0; i < capacity; i++)
	{
		hashtable[i].value = NULL_TELEM;
		hashtable[i].next = -1;
		hashtable[i].line = -1;
		hashtable[i].column = -1;
	}
	currentNumberOfElements = 0;
}
//Theta(capacity)

Matrix::Matrix(int nrLines, int nrCols) {
	numberOfColumns = nrCols;
	numberOfLines = nrLines;
	divisorUsedForHashing = capacity = 10;

	hashtable = new elementOfHashtable[capacity];
	emptyHashtable();
}

int Matrix::hash(int i, int j) const
{
	int primeNumberUsedForHashing = 31;
	return (1LL * i + 1LL * primeNumberUsedForHashing * j) % divisorUsedForHashing;
}
//Theta(1)

int Matrix::getFirstEmptyPosition()
{
	for (int i = 0; i < capacity; i++)
	{
		if (hashtable[i].value == NULL_TELEM)
		{
			return i;
		}
	}
	return -1;
}
//Best case: Theta(1), Worst case: Theta(currentNumberOfElements) => Total complexity O(currentNumberOfElements)

int Matrix::nrLines() const {
	return numberOfLines;
}
//Theta(1)

int Matrix::nrColumns() const {
	return numberOfColumns;
}
//Theta(1)

TElem Matrix::element(int i, int j) const {
	if (i < 0 || j < 0 || i >= numberOfLines || j >= numberOfColumns)
	{
		throw exception();
	}

	int position = hash(i, j);
	while (position != -1)
	{
		if (position == hashtable[position].next)
			cout << "loop\n";
		if (hashtable[position].column == j && hashtable[position].line == i)
		{
			return hashtable[position].value;
		}
		position = hashtable[position].next;
	} 

	return NULL_TELEM;
}
//Best case: Theta(1), Worst case: Theta(currentNumberOfElements) => Total complexity O(currentNumberOfElements)

void Matrix::deleteElementFromPosition(int position)
{
	hashtable[position].value = NULL_TELEM;
	if (hashtable[position].next != -1)
		resizeAndRehash(1);
}
//Best case: Theta(1)
//Worst case: Theta(capacity + currentNumberOfElements^2) (impossible?)
//Total complexity: O(capacity + currentNumberOfElements^2)
//Note: the average case is MUCH better than the Total Complexity

void Matrix::deleteElement(int i, int j, int position, int previousPosition)
{
	if (i == 800 && j == 8)
		cout << -1;

	if (hashtable[previousPosition].line == 800 && hashtable[previousPosition].column == 8)
		cout << -3;

	currentNumberOfElements--;
	int initialPos = position;
	int newLastPosition = position;
	while (hashtable[position].next != -1 )
	{
		newLastPosition = position;
		position = hashtable[position].next;
	}

	int search = false;
	if (hashtable[position].line == 800 && hashtable[position].column == 8)
	{
		cout << hash(800, 8) << ' ' << hash(i, j) << '\n';
		cout << element(800,8) << ' ';
		cout << element(i, j) << ' ';
		search = true;
	}
		

	hashtable[initialPos].value = hashtable[position].value;
	hashtable[initialPos].line = hashtable[position].line;
	hashtable[initialPos].column = hashtable[position].column;

	hashtable[position].value = NULL_TELEM;
	hashtable[position].line = -1;
	hashtable[position].column = -1;
	hashtable[position].next = -1;

	//if (newLastPosition != hash(hashtable[initialPos].line, hashtable[initialPos].column))
		hashtable[newLastPosition].next = -1;

	if ( (position == initialPos && previousPosition != -1) || (newLastPosition == initialPos))
	{
		hashtable[previousPosition].next = -1;
	}

	if (search)
		//cout << hash(800, 8) << ' ';
		cout << element(800, 8) << '\n';
}
//I don't use this one, it doesn't work

TElem Matrix::tryToModify(bool &worked, int i, int j, TElem e)
{
	int position = hash(i, j);
	int previousPosition = -1;
	TElem oldValue = element(i, j);

	if (oldValue == NULL_TELEM)
		return oldValue;

	while (position != -1)
	{
		if (hashtable[position].column == j && hashtable[position].line == i)
		{
			worked = true;
			if (e != NULL_TELEM)
			{
				hashtable[position].value = e;
			}
			else if (e == NULL_TELEM)
			{	
				deleteElementFromPosition(position);
			}
			return oldValue;
		}
		
		if (position == hashtable[position].next)
			cout << "UPS 2";
		previousPosition = position;
		position = hashtable[position].next;
	} 
}
//Best case: Theta(1)
//Worst case: Theta(capacity + currentNumberOfElements^2) (impossible?)
//Total complexity: O(capacity + currentNumberOfElements^2)
//Note: the average case is MUCH better than the Total Complexity

void Matrix::insert(int i, int j, TElem e)
{
	if (e == NULL_TELEM)
		return;

	if (loadFactor <= currentNumberOfElements / capacity)
		resizeAndRehash();

	currentNumberOfElements++;
	int position = hash(i, j);
	if (hashtable[position].value == NULL_TELEM)
	{
		hashtable[position].value = e;
		hashtable[position].line = i;
		hashtable[position].column = j;
		hashtable[position].next = -1;
		return;
	}

	int firstEmptyPosition = getFirstEmptyPosition();
	if (firstEmptyPosition == -1)
		cout << "UPS" << '\n';

	int current = position;
	while (hashtable[current].next != -1 && hashtable[current].value != NULL_TELEM)
	{
		current = hashtable[current].next;
	}
	hashtable[firstEmptyPosition].value = e;
	hashtable[firstEmptyPosition].line = i;
	hashtable[firstEmptyPosition].column = j;
	hashtable[firstEmptyPosition].next = -1;
	if (firstEmptyPosition != current && hashtable[current].value != NULL_TELEM)
		hashtable[current].next = firstEmptyPosition;
}
//Best case: Theta(1), Worst case without rehash Theta(currentNumberOfElements), Worst case with rehash Theta(capacity + currentNumberOfElements^2)
//Total complexity: O(currentNumberOfElements) without rehash
//Total complexity: O(capacity + currentNumberOfElements^2) with rehash
//Note: the average case is MUCH better than the Total Complexity


TElem Matrix::modify(int i, int j, TElem e) 
{
	if (i < 0 || j < 0 || i >= numberOfLines || j >= numberOfColumns)
	{
		throw exception();
	}

	bool matrixWasModified = false;
	TElem result = tryToModify(matrixWasModified, i, j, e);
	if (matrixWasModified)
	{
		return result;
	}
	
	insert(i, j, e);
	return NULL_TELEM;
}
//Best case: Theta(1)
//Worst case: Theta(capacity + currentNumberOfElements^2) (impossible?)
//Total complexity: O(capacity + currentNumberOfElements^2)
//Note: the average case is MUCH better than the Total Complexity

int Matrix::numberOfNonZeroElements(int col) const
{
	if (col < 0 || col >= numberOfColumns)
	{
		throw exception();
	}

	int result = 0;
	for (int i = 0; i < numberOfLines; i++)
	{
		if (element(i, col) != 0)
			result++;
	}

	return result;
}
//Best case: Theta(number of rows), Worst case: Theta(number of rows * capacity)