#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) 
{
	relation = r;
	numberOfElements = 0;
	head = tail = nullptr;
}
//Theta(1)

bool SortedSet::add(TComp elem) 
{
	if (numberOfElements == 0)
	{
		head = new DLLNode(elem, nullptr, nullptr);
		numberOfElements++;
		return true;
	}
	if (numberOfElements == 1)
	{
		if (head->element == elem)
			return false;
		if (relation(elem, head->element))
		{
			tail = head;
			head = new DLLNode(elem, tail, nullptr);
			tail->previous = head;
			numberOfElements++;
			return true;
		}
		tail = new DLLNode(elem, nullptr, head);
		head->next = tail;
		numberOfElements++;
		return true;
	}


	PointerToNode currentNode = head;
	while (currentNode != nullptr && relation(currentNode->element, elem)) //!!! MIGHT EXPLODE BECAUSE 
	{ //WE DO currentNode->element WHEN currentNode is nullptr
		if (elem == currentNode->element)
		{
			return false;
		}
		currentNode = currentNode->next;
	}

	if (currentNode == head) //elem < head->element
	{
		PointerToNode newNode = new DLLNode(elem, head, nullptr);
		head->previous = newNode;
		newNode->next = head;
		head = newNode;
		numberOfElements++;
		return true;
	}
	
	if (currentNode == nullptr) // elem > tail->element
	{
		PointerToNode newNode = new DLLNode(elem, nullptr, tail);
		tail->next = newNode;
		tail = newNode;
		numberOfElements++;
		return true;
	}

	//we arrive here if currentNode.element > elem and elem > currentNode.previous.element
	//so it need to go between currentNode and currentNode.previous
	PointerToNode newNode = new DLLNode(elem, currentNode, currentNode->previous);
	currentNode->previous->next = newNode;
	currentNode->previous = newNode;

	numberOfElements++;
	return true;
}
//Best: Theta(1), Worst: Theta(numberOfElements) => Total Compexity O(numberOfElements)


bool SortedSet::remove(TComp elem) {
	bool removed = false;
	PointerToNode currentNode = head;

	if (numberOfElements == 0)
		return false;

	if (numberOfElements == 1)
	{
		if (head->element == elem)
		{
			PointerToNode p = head;
			head = nullptr;
			delete p;
			numberOfElements = 0;
			return true;
		}
		return false;
	}

	if (head->element == elem)
	{
		PointerToNode p = head;
		head = head->next;
		delete p;
		numberOfElements--;
		return true;
	}

	if (tail->element == elem)
	{
		PointerToNode p = tail;
		tail = tail->previous;
		tail->next = nullptr;
		delete p;
		numberOfElements--;
		return true;
	}

	while (currentNode != nullptr && relation(currentNode->element, elem)) //!!! MIGHT EXPLODE BECAUSE 
	{ //WE DO currentNode->element WHEN currentNode is nullptr
		if (elem == currentNode->element)
		{
			PointerToNode p = currentNode;
			currentNode->previous->next = currentNode->next;
			currentNode->next->previous = currentNode->previous;
			delete p;
			numberOfElements--;
			return true;
		}
		currentNode = currentNode->next;
	}
	return false;
}
//Best: Theta(1), Worst: Theta(numberOfElements) => Total Compexity O(numberOfElements)


bool SortedSet::search(TElem elem) const
{
	bool found = false;
	PointerToNode currentNode = head;

	while (currentNode != nullptr && relation(currentNode->element, elem)) //!!! MIGHT EXPLODE BECAUSE 
	{ //WE DO currentNode->element WHEN currentNode is nullptr
		if (elem == currentNode->element)
		{
			found = true;
			break;
		}
		currentNode = currentNode->next;
	}
	return found;
}
//Best: Theta(1), Worst: Theta(numberOfElements) => Total Compexity O(numberOfElements)

/*bool SortedSet::search(TComp elem) const
{
	bool found = false;
	PointerToNode currentNode = head;

	while (currentNode != nullptr && relation(currentNode->element, elem)) //!!! MIGHT EXPLODE BECAUSE 
	{ //WE DO currentNode->element WHEN currentNode is nullptr
		if (elem == currentNode->element)
		{
			found = true;
			break;
		}
		currentNode = currentNode->next;
	}
	return found;
}*/
//Best: Theta(1), Worst: Theta(numberOfElements) => Total Compexity O(numberOfElements)

int SortedSet::size() const {
	return numberOfElements;
}
//Theta(1)


bool SortedSet::isEmpty() const {
	if (numberOfElements == 0)
		return true;
	return false;
}
//Theta(1)

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	while (head != nullptr)
	{
		PointerToNode node = head;
		head = head->next;
		delete node;
	}
}
//Theta(numberOfElements)

