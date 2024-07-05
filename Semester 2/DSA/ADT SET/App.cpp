#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
using namespace std;

int main() {

    //Extra assigment
    Set S1;
    S1.add(1);
    S1.add(2);
    S1.add(4);
    S1.add(3);
    S1.add(7);
    S1.add(6);

    Set S2;
    S2.add(1);
    S2.add(1);
    S2.add(2);
    S2.add(5);
    S2.add(6);

    S1.intersection(S2);
    SetIterator it = S1.iterator();
    it.first();
    while (it.valid()) {
        TElem e = it.getCurrent();
        cout << e << " ";
        it.next();
    }

	//testAll();
    //testAllExtended();

	cout << "That's all!" << endl;
	system("pause");

}



