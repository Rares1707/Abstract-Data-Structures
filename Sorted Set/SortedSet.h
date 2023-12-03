#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;

struct DLLNode;
typedef DLLNode* PointerToNode;
struct DLLNode {
	TElem element;
	PointerToNode next;
	PointerToNode previous;
	DLLNode(TElem elementOfNode, PointerToNode nextElement, PointerToNode previousElement) {
		this->element = elementOfNode;
		this->next = nextElement;
		this->previous = previousElement;
	}
};

class SortedSet {
	friend class SortedSetIterator;
private:
	PointerToNode head;
	PointerToNode tail;
	Relation relation;
	int numberOfElements;
	// !!! README: the Search function had a TComp as the parameter in the .cpp file and 
	// a TElem as the parameter in the .h file, so I created another Search function in the .cpp which
	// respects the header's definition

public:
	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();


};
