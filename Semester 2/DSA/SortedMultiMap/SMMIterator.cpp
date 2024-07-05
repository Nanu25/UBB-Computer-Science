
#include "SMMIterator.h"
#include "SortedMultiMap.h"

//BC = WC = TC = Theta(1)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    //TODO - Implementation
    this->index = this->map.elems.head;
}

//BC = WC = TC = Theta(1)
void SMMIterator::first(){
    //TODO - Implementation
    this->index = this->map.elems.head;
}

//BC = WC = TC = Theta(1)
void SMMIterator::next(){
    //TODO - Implementation
    if(this->valid())
        this->index = this->map.elems.list[index].next;
    else
        throw std::exception();
}

//BC = WC = TC = Theta(1)
bool SMMIterator::valid() const{
    //TODO - Implementation
    return this->index != -1;
}

//BC = WC = TC = Theta(1)
TElem SMMIterator::getCurrent() const{
    if(this->valid())
        return this->map.elems.list[index].info;
    else
        throw std::exception();

}