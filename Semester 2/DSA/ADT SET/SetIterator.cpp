#include "SetIterator.h"
#include "Set.h"


///BC = WC = TC = Theta(1)
SetIterator::SetIterator(const Set& m) : set(m)
{
    this->currentPosition = 0;
}

///BC = WC = TC = Theta(1)
void SetIterator::first() {
    this->currentPosition = 0;
}

///BC = WC = TC = Theta(1)
void SetIterator::next() {
    if(this->currentPosition == this->set.setSize)
        throw std::exception();

    this->currentPosition++;
}

///BC = WC = TC = Theta(1)
TElem SetIterator::getCurrent()
{
    if(this->currentPosition == this->set.setSize)
        throw std::exception();

	return this->set.elements[this->currentPosition];
}

///BC = WC = TC = Theta(1)
bool SetIterator::valid() const {
	return this->currentPosition < this->set.setSize;
}



