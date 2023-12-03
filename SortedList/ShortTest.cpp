#include <assert.h>
#include "iostream"
#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}

bool condition1(TComp element)
{
    return element % 2 == 0;
}

void testFilter()
{
    SortedIndexedList list = SortedIndexedList(relation1);
    assert(list.size()==0);
    list.filter(condition1);
    assert(list.size() == 0);
    list.add(3);
    list.add(1);
    list.add(6);
    list.add(2);
    list.add(0);
    list.filter(condition1);
    assert(list.size()==3);
    assert(list.search(0) != -1);
    assert(list.search(2) != -1);
    assert(list.search(6) != -1);
    assert(list.search(1) == -1);
    assert(list.search(3) == -1);
    std::cout << "Filter works\n";
}