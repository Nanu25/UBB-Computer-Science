#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

///BC = WC = TC = Theta(1)
SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation
    this->r = r;
}

///BC = WC = TC = Theta(1)
int SortedIndexedList::size() const {
	//TODO - Implementation
    return this->sorted_list.getSize();
}

///BC = WC = TC = Theta(1)
bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
    return this->size() == 0;
}

///BC = Theta(1)
///WC = Theta(n)
///TC = O(n)
TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation
    if(i < 0 || i >= this->size())
        throw std::exception();

    Node *element = this->sorted_list.getHead();
    int index = 0;
    while(index < i && element != nullptr) {
        index++;
        element = element->next;
    }
	return element->data;
}

///BC = Theta(1)
///WC = Theta(n)
///TC = O(n)
TComp SortedIndexedList::remove(int i) {
    //TODO - Implementation
    if (i == -1 || i >= size()) {
        throw std::exception();
    }

    Node *prev_node = nullptr;
    Node *current_node = this->sorted_list.getHead();

    int current_position = 0;
    while (current_position < i && current_node != nullptr) {
        prev_node = current_node;
        current_node = current_node->next;
        current_position++;
    }

    if (prev_node == nullptr && current_node != nullptr) {  //first position
        this->sorted_list.setHead(current_node->next);
        this->sorted_list.setSize(this->sorted_list.getSize() - 1);
    } else if (current_node != nullptr) {
        prev_node->next = current_node->next;
        current_node->next = nullptr;
        this->sorted_list.setSize(this->sorted_list.getSize() - 1);
    }
    return current_node->data;
}

///BC = Theta(1)
///WC = Theta(n)
///TC = O(n)
int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
    Node *element = this->sorted_list.getHead();
    int position = 0;
    while(element != nullptr && element->data != e) {
        position++;
        element = element->next;
    }
	return (position != this->size() ? position : -1);
}

///BC = Theta(1)
///WC = Theta(n)
///TC = O(n)
void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
    Node *element = this->sorted_list.getHead();
    int position = 0;
    while(element != nullptr && this->r(e, element->data) == 0) {       //search the position to fit my element.
        position++;
        element = element->next;
    }

    if(position == 0) {
        Node *new_node = new Node();
        new_node->data = e;
        new_node->next = this->sorted_list.getHead();

        this->sorted_list.setHead(new_node);
        this->sorted_list.setSize(this->sorted_list.getSize() + 1);
    }else {
        Node *element_from_pos = this->sorted_list.getHead();
        int pos = 0;
        while(pos < position - 1 && element_from_pos != nullptr) {
            pos++;
            element_from_pos = element_from_pos->next;
        }

        if(element_from_pos != nullptr) {
            Node *new_node = new Node();
            new_node->data = e;
            new_node->next = element_from_pos->next;

            element_from_pos->next = new_node;
            this->sorted_list.setSize(this->sorted_list.getSize() + 1);
        }
    }
}

///BC = WC = TC = Theta(1)
ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
///BC = Theta(n)
///WC = Theta(n)
///TC = Theta(n)
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
    Node *current = this->sorted_list.getHead();
    while(current != nullptr) {
        Node *element = current->next;
        delete current;
        current = element;
    }
}


///BC = WC = AC = Theta(N), N is the size of the list.
int SortedIndexedList::removeAll(SortedIndexedList &list) {
    int number_removed = 0;
    while(list.isEmpty() == 0) {
        number_removed++;
        list.remove(0);     //always remove the first position for a better complexity
    }
    return number_removed;
}


