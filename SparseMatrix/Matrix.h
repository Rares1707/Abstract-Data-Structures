#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0


typedef struct {
	int column;
	int line;
	TElem value;
	int next;
}elementOfHashtable;

class Matrix {

private:


	int numberOfLines;
	int numberOfColumns;

	int capacity;
	int currentNumberOfElements;
	elementOfHashtable* hashtable;

	const double loadFactor = 0.7;
	int divisorUsedForHashing;

	void insert(int i, int j, TElem e);
	TElem tryToModify(bool& worked, int i, int j, TElem e);
	int getFirstEmptyPosition();
	void resizeAndRehash(int); //will be called when currentNumberOfElements / capacity > loadFactor
	int hash(int i, int j) const;
	void emptyHashtable();
	void deleteElement(int i, int j, int position, int previousPosition);
	void deleteElementFromPosition(int position);


public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	int numberOfNonZeroElements(int col) const;

};
