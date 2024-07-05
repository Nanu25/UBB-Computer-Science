#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

///BC = WC = TC = Theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
    this->i = this->list.sorted_list.getHead();

}

///BC = WC = TC = Theta(1)
void ListIterator::first(){
	//TODO - Implementation
    this->i = this->list.sorted_list.getHead();
}

///BC = WC = TC = Theta(1)
void ListIterator::next(){
	//TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }
    this->i = this->i->next;
}

///BC = WC = TC = Theta(1)
bool ListIterator::valid() const{
	//TODO - Implementation
	return (this->i != NULL);
}

///BC = WC = TC = Theta(1)
TComp ListIterator::getCurrent() const{
	//TODO - Implementation
    return this->i->data;
}