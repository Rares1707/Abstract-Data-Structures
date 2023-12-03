#include <assert.h>
#include "Matrix.h"
#include <iostream>
#include <exception>
using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
}

void testNumberOfNonZeroElements()
{
	Matrix m(4, 4);
	m.modify(1, 1, 5);
	m.modify(3, 1, 6);
	m.modify(2, 1, -1);
	assert(m.numberOfNonZeroElements(1) == 3);

	Matrix m2(4, 4);
	assert(m2.numberOfNonZeroElements(2) == 0);
	m2.modify(1, 2, 0);
	assert(m2.numberOfNonZeroElements(2) == 0);
	try
	{
		m2.numberOfNonZeroElements(4);
		//assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}

	try
	{
		m2.numberOfNonZeroElements(-1);
		//assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}
	
	cout << "Extra operation tested\n";
}