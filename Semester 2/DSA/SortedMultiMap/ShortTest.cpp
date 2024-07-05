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

bool condition(TValue x) {
    return x > 5;
}

void test_new_function() {
    SortedMultiMap smm = SortedMultiMap(relation1);
    smm.add(10, 6);
    smm.add(6, 7);
    smm.add(30, 9);
    smm.add(5, 2);

    assert(smm.size() == 4);
    smm.filter(condition);

    SMMIterator it = smm.iterator();
    while (it.valid()){
        TElem e = it.getCurrent();
        std::cout << e.first << "  " << e.second << '\n';
        it.next();
    }
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

