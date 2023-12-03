#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
typedef bool (*Condition)(TComp);
#define NULL_TCOMP -11111

struct BSTNode;
typedef BSTNode* PointerToNode;
struct BSTNode {
    TComp element;
    PointerToNode left;
    PointerToNode right;
    int numberOfElementsToTheLeft;
    BSTNode(TComp elementOfNode, PointerToNode leftNode, PointerToNode rightNode, int nrElementsToLeft) {
        this->element = elementOfNode;
        this->left = leftNode;
        this->right = rightNode;
        this->numberOfElementsToTheLeft = nrElementsToLeft;
    }
};

class SortedIndexedList {
private:
	friend class ListIterator;
private:
    PointerToNode root;
    Relation relation;
    int currentNumberOfElements;

    PointerToNode insert(PointerToNode currentNode, TComp e);
public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element in the sortedList (to the corresponding position)
	void add(TComp e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

    //(this is the extra functionality) keeps in the SortedList only elements that respect the given condition
    void filter(Condition cond);

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();
};
