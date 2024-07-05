#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


///BC : Theta(1)
///WC : Theta(m)
///TC : O(m)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	//TODO - Implementation
    if(bag.isEmpty()) {
        this->currentPos = -1;
        this->currentNode = nullptr;
    }else {
        this->currentPos = 0;
        while(this->currentPos < this->bag.m && this->bag.htable[this->currentPos] == nullptr)
            this->currentPos++;
        this->currentNode = this->bag.htable[currentPos];
    }
}

///BC : Theta(1)
///WC : Theta(m)
///TC : O(m)
void BagIterator::first() {
	//TODO - Implementation
    if (bag.isEmpty()) {
        throw std::exception();
    }
    this->currentPos = 0;
    while (this->bag.htable[this->currentPos] == nullptr) {
        this->currentPos++;
    }
    this->currentNode = this->bag.htable[this->currentPos];
}


///BC : Theta(1)
///WC : Theta(m)
///TC : O(m)
void BagIterator::next() {
	//TODO - Implementation
    if (this->currentPos == -1 or this->currentNode == nullptr) {
        throw std::exception();
    }
    this->currentNode = this->currentNode->next;
    if (this->currentNode == nullptr) {
        this->currentPos ++;
        while(this->currentPos  < bag.m and bag.htable[this->currentPos ] == nullptr) {
            this->currentPos ++;
        }
        if (this->currentPos  == bag.m) {
            this->currentPos  = -1;
        }else {
            this->currentNode = bag.htable[this->currentPos ];
        }
    }
}

///BC = WC = TC = Theta(1)
bool BagIterator::valid() const {
	//TODO - Implementation
	return this->currentPos != -1 && this->currentNode != nullptr;
}

///BC = WC = TC = Theta(1)
TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
    if(this->currentPos == -1)
        throw std::exception();

	return this->currentNode->key;
}
