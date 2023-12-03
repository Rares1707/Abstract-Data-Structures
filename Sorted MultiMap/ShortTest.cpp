#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testReplace()
{
    SortedMultiMap smm = SortedMultiMap(relation1);
    smm.replace(3, 4, 5);
    assert(smm.isEmpty());
    smm.add(1, 3);
    smm.add(1, 3);
    smm.add(5, 3);
    smm.add(1, 3);
    smm.replace(1, 3, -11);
    assert(smm.size() == 4);

    auto it = smm.iterator();
    assert(it.getCurrent().first == 1 && it.getCurrent().second == -11);
    it.next();
    assert(it.getCurrent().first == 1 && it.getCurrent().second == -11);
    it.next();
    assert(it.getCurrent().first == 1 && it.getCurrent().second == -11);
    it.next();
    assert(it.getCurrent().first == 5 && it.getCurrent().second == 3);
    cout << "Replace works!\n";
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);

    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
   
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}

