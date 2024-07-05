#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#include <vector>

#define NULL_TELEM -111111;
#define ALPHA 0.75
typedef int TElem;
class BagIterator; 
class Bag {

private:
	//TODO - Representation
    struct Node {
        int key;
        Node* next;
    };

    int m;
    Node** htable;
    int cap, sizeH;
    void resize(int newcap);
    int h(TElem elem) const;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();

    ///Extra
    std::vector <int> histogram();

};