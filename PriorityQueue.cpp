#include "PriorityQueue.hpp"
#include <limits.h>
using namespace std;

void swap(ItemInfo *a, ItemInfo *b)
{
	// TODO
	ItemInfo temp = *a;
	*a = *b;
	*b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ()
{
	// TODO
	capacity = 50;
	heapArr = new ItemInfo[capacity];
	currentSize = 0;

}

PriorityQ::PriorityQ(int cap)
{
    capacity = cap;
    heapArr = new ItemInfo[capacity];
    currentSize = 0;
}



///////////////////////////////////////////
PriorityQ::~PriorityQ() {
    delete[] heapArr; // important deallocationg
}
///////////////////////////////////////////


/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
	// TODO
	return (index -1)/2;

}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
	// TODO
	return (2 * index +1);

}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
	// TODO
	return (2 * index +2);

}

ItemInfo* PriorityQ::peek()
{
	// TODO
	if (currentSize == 0){
		return nullptr;
	}
	return &heapArr[0];
}

void PriorityQ::heapify(int i)
{
	// TODO
	int left = leftChild(i);
    int right = rightChild(i);
    int largest = i;

    if (left < currentSize && heapArr[left].damage > heapArr[largest].damage){ // compare by damage
        largest = left;
	} if (right < currentSize && heapArr[right].damage > heapArr[largest].damage){
        largest = right;
	} if (largest != i) {
        swap(&heapArr[i], &heapArr[largest]);
        heapify(largest);
    }

}

void PriorityQ::insertElement(ItemInfo item)
{
	// TODO
	if (currentSize == capacity){
        cout << "Heap full, cannot insert" << endl;
        return;
    }

    // insert at end
    int i = currentSize;
    heapArr[i] = item;
    currentSize++;

    // bubble up
    while (i != 0 && heapArr[parent(i)].damage < heapArr[i].damage) {
        swap(&heapArr[i], &heapArr[parent(i)]);
        i = parent(i);
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
	// TODO
	if (currentSize == 0) {
        cout << "empty" << endl;
        return;
    }

    for (int i = 0; i < currentSize; i++) {
		cout << "=======================" << endl;
        cout << heapArr[i].characterName << ": " << endl;
        cout << heapArr[i].itemName << ": " << endl;
    	cout << heapArr[i].damage << ": "<< endl;
        cout << heapArr[i].comment << endl;
		cout << "=======================" << endl;
    }
}

// Optional function, use if you need to
void PriorityQ::popHelper(int i) {
	// TODO
	heapify(i);
	
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
	// TODO
	if (currentSize == 0){
        return;   // empty pop
	}

    heapArr[0] = heapArr[currentSize - 1]; // overwrite root with last element
    currentSize--;

    heapify(0); // fix heap
}
