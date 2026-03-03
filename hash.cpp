// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"
#include<sstream>


using namespace std;

/////////////////////////////////////////////////
HashTable::~HashTable() {
	for (int i = 0; i < tableSize; ++i) {
    	node* curr = table[i];
	
    	while(curr) {
     	 node* next = curr->next;
     	 delete curr; //frees heapArr
      	curr = next;
		}
    }
	delete[] table;
  }
/////////////////////////////////////////////////

node* HashTable::createNode(string charName, node* nextNode)
{
	// TODO
	node *chtr = new node;
	chtr->characterName = charName;

	chtr->next = nextNode;
	return chtr;
}


HashTable::HashTable(int bsize)
{
	// TODO
	tableSize = bsize;
	table = new node *[tableSize];

	for(int i =0; i < tableSize; i++){ // constructing buckets
		table[i] = nullptr;
	}
	numCollision = 0;

}


void HashTable::printTable()
{
    for(int i = 0; i < tableSize; i++){
        cout << "table[" << i << "]: ";

        node *current = table[i];
        bool first = true;

        while (current) {
            if (!first) cout << ", ";
            cout << current->characterName;
            first = false;
            current = current->next;
        }
        cout << endl;
    }
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string charName)
{
    unsigned int sum = 0;
    for (unsigned char c : charName) {
        sum += c;
    }
    return sum % tableSize;
}

node* HashTable::searchCharacter(string charName)
{
	// TODO
	int start = hashFunction(charName);
	node *curr = table[start];

	while(curr){
		if (curr->characterName == charName){
			return curr;
		}
		curr = curr->next;
	}
	return nullptr;
}

//function to insert
void HashTable::insertItem(ItemInfo newItem)
{
    int index = hashFunction(newItem.characterName);
    node *start = table[index];

    for (node *curr = start; curr != nullptr; curr = curr->next){
        if(curr->characterName == newItem.characterName){
            curr->pq.insertElement(newItem);
            return;
        }
    }

    node *chtr = createNode(newItem.characterName, start);
    chtr->pq.insertElement(newItem);

    if (start != nullptr) {
        numCollision++;
    }
    table[index] = chtr;   // ALWAYS set this
}

void HashTable:: buildBulk(string fname)
{
    // TODO
	 ifstream infile(fname);
    if (!infile.is_open()) {
        cout << "wrong file name." << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        if (line.empty()){ 
			continue;
		}

        string character;
		string item;
		string dmgStr;
		string comment;
        stringstream ss(line);

        getline(ss, character, ';');
        getline(ss, item, ';');
        getline(ss, dmgStr, ';');
        getline(ss, comment);

        if(character.empty() || item.empty() || dmgStr.empty()){
            continue;
		}
        ItemInfo chtr{character, item, stoi(dmgStr), comment};
        insertItem(chtr);
    }


}

void HashTable::deleteEntry(string charName) {
	// TODO
	int starting = hashFunction(charName);
	node *current = table[starting];
	node *previous = nullptr;

	while(current && current->characterName != charName){
		previous = current;
		current = current->next;
	} if( !current){
		cout << "no record found." << endl; // could not find
		return;
	} if (previous){
		previous->next = current->next;
	} else {
		table[starting] = current->next;
	}
	delete current; // deallocating

}
