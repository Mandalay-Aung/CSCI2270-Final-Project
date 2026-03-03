#include<iostream>
#include <vector>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "hash.hpp"
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"

using namespace std;
using namespace std::chrono;

void displayMenu()//keep it in starter code
{
    cout<<"------------------"<<endl;
    cout<<"1: Build the datastructure (call it only once)"<<endl;
    cout<<"2: Add a new item"<<endl;
    cout<<"3: Peek most powerful item from character"<<endl;
    cout<<"4: Pop most powerful item from character"<<endl;
    cout<<"5: Print all items for character"<<endl;
    cout<<"6: Get number of collisions"<<endl;
    cout<<"7: Print the table"<<endl;
	cout<<"8: Find easiest route through dungeon"<<endl;
    cout<<"9: Exit"<<endl;
    cout<<"------------------"<<endl;

}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct num of arg"<<endl;
        return 0;
    }
    string fname =argv[1];
    int tableSize = stoi(argv[2]);
    
    int ch = 0;
    string chs;
    HashTable ht(5);
    bool built = false;
    while(ch!=9)
    {
        displayMenu();
        cout<<"Give your choice >> ";
        getline(cin, chs);
        ch =stoi(chs);
        switch (ch)
        {
            case 1:{ // bulk build (should only build on first call)
				// TODO
                if(built){
                    cout << "This was already built!" << endl; // cannot call twice
                    break;
                }
                ht.buildBulk(fname); // if not called already, buildBulk true
                built = true;
                break;
            }
            case 2:{ // Insert new items from console
				// TODO
                cout << "Charater Name: "; // input characterName,itemName, damage, and comment accordingly
                string characterName;
                getline(cin, characterName);
                cout << "Item Name: ";
                string itemName;
                getline(cin, itemName);
                cout << "Item Damage: ";
                string itemDamage;
                getline(cin, itemDamage);
                cout << "Item Comment: ";
                string itemComment;
                getline(cin, itemComment);

                ItemInfo shawty{characterName, itemName, stoi(itemDamage), itemComment}; // manually insert into the hash table
                ht.insertItem(shawty);
                break;
            }
            case 3:{ // Peek 
				//TODO
                cout << "Enter Character Name: ";
                string characterName;
                getline(cin, characterName);

                node *character = ht.searchCharacter(characterName); // going into hash table to retreive character
                if (!character){
                    cout << "no record found." <<endl; // wasnt found
                    break;
                }
                ItemInfo *geeker = character->pq.peek(); // most powerful weapon geeked
                if(!geeker){
                    cout << "no record found." << endl; // was not found
                    break;
                } 

                cout << "retrieving results ~~~~~~~~" << endl; // printing info if found
                cout << "Character Name: "<< geeker->characterName << endl;
                cout << "Item Name: "<< geeker->itemName << endl;
                cout << "Item Damage: "<< geeker->damage << endl;
                cout << "Comment: "<< geeker->comment << endl;
                break;

			}
            case 4:{ // Pop
				// TODO
                cout << "Enter Character Name: ";
                string characterName;
                getline(cin, characterName);

                node *character = ht.searchCharacter(characterName); // going into hash table to retreive character
                if (!character){
                    cout << "no record found." <<endl; // wasnt found
                    break;
                }if(character->pq.peek() == nullptr){
                    cout << "no record found." << endl;
                    break;
                }
                character->pq.pop();
                break;
    
            }
            case 5:{ // Print all items for character
				// TODO
                cout << "Enter Character Name: ";
                string characterName;
                getline(cin, characterName);
                node *character = ht.searchCharacter(characterName); // going into hash table to retreive character
                if (!character){
                    cout << "no record found." <<endl; // wasnt found
                    break;
                }

                character->pq.print(); // going into priority queue and printing
                break;
			}
            case 6: { // Display collisions
				// TODO
                cout << ht.getNumCollision() << endl;
                break;
			}
            case 7: { // Print table
				// TODO
                ht.printTable();
                break;
			}
			case 8:{ // Find easiest path through dungeon
				cout << "Input dungeon(file name): " << endl;
				string dungeonFile;
				getline(cin, dungeonFile);
				EnemyGraph G;
				G.buildGraphFromFile(dungeonFile);
				cout << G.findEasiestPath(ht) << endl;
				break;
			}
			case 9:
				cout << "Goodbye..." << endl;
				break;
       
            default:
                cout<<"Give a valid entry"<<endl;
                break;
        }
    }
}
