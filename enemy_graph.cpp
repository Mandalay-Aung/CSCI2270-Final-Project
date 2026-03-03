#include "enemy_graph.hpp"
#include <iostream>

EnemyGraph::EnemyGraph() {
	return;
}

EnemyGraph::~EnemyGraph() {
    for (auto entry : vertices) {
        delete entry.second;
    }
    vertices.clear();
}

Vertex* EnemyGraph::addVertex(string id) {
    // Check for unique ID
    if (vertices.count(id) > 0) {
        cout << "ID already exists: " << id << endl;
        return nullptr;
    }
    Vertex* v = new Vertex();
    v->id = id;
	v->distance = 0;
	v->solved = false;
    vertices.insert({id, v});
    return v;
}

Vertex* EnemyGraph::searchVertex(string id) {

	Vertex* toReturn = nullptr;
	for (auto entry : vertices) {
		if (entry.first == id)
			return entry.second;
	}

    if (toReturn==nullptr) {
            throw std::invalid_argument("Vertex not found with provided id");
    }
	return toReturn;
}

/**
 * Adds an undirected edge between two vertices with specified IDs.
 */
void EnemyGraph::addEdge(string v1_id, string v2_id, string enemy_id) {
    // Verify that the IDs exist and are unique
    if (v1_id == v2_id) {
        cout << "v1_id and v2_id must be different!" << endl;
        return;
    }
    if (vertices.count(v1_id) == 0) {
        cout << "No Vertex with ID: " << v1_id << endl;

        return;
    }
    if (vertices.count(v2_id) == 0) {
        cout << "No Vertex with ID: " << v2_id << endl;
        return;
    }

    Vertex* v1 = vertices.at(v1_id);
    Vertex* v2 = vertices.at(v2_id);

    // Verify that edge doesn't already exist
    for (const auto &v : v1->adjacent) {
        if (v.v->id == v2_id) {
            cout << "There is already an edge between " << v1_id << " and " << v2_id << endl;
            return;
        }
    }
    for (const auto &v : v2->adjacent) {
        if (v.v->id == v1_id) {
            cout << "There is already an edge between " << v1_id << " and " << v2_id << endl;
            return;
        }
    }

    AdjacentVertex adj_v2;
    adj_v2.v = v2;
    adj_v2.enemy_id = enemy_id;
    v1->adjacent.push_back(adj_v2);

    AdjacentVertex adj_v1;
    adj_v1.v = v1;
    adj_v1.enemy_id = enemy_id;
    v2->adjacent.push_back(adj_v1);
}

/**
 *
 */
void EnemyGraph::buildGraphFromFile(string fname) 
{
    
    ifstream ifile;
    ifile.open(fname.c_str());
    if( !ifile.is_open())
    {
        cout<<"wrong file name or path"<<endl;
        return;
    }
    string line;
    while(getline(ifile,line))
    {
        stringstream s(line);
        string type; // vertex or edge
		string vertex_ID; // data for vertex
		string vertex1, vertex2, charName; // data for edges
        getline(s,type,';'); //cout<<movieName<<endl;
		if (type == "vertex") {
        	getline(s,vertex_ID,';'); 
			addVertex(vertex_ID);
		} else if (type == "edge") {
        	getline(s,vertex1,';');
        	getline(s,vertex2,';'); 
        	getline(s,charName,';'); 
			addEdge(vertex1, vertex2, charName);
		} else {
			cout << "line read error..." << endl;
		}
    }
    
}

/**
 *  Your implmentation should run a Dijkstra's search from the start vertext to the end
 *   - Edges are labeled with character names, 
 *   - Edge weights will be the character's highest damage item
 */
int EnemyGraph::findEasiestPath(const HashTable& ht) {
	//TODO
    if (vertices.count("start") == 0 || vertices.count("end") == 0){ // checking start/end valid
        cout  << "error." << endl;
        return -1;
    }

    Vertex *startVert = vertices["start"];
    Vertex *endVert = vertices["end"];
    for(auto &path : vertices){ // initalizing all distances and marking unsolved
        path.second->distance = INT_MAX;
        path.second->solved = false;
    }
    startVert->distance = 0;
    PriorityQ  pq(500); // PQ is a MAX heap so insert with negative priority

    ItemInfo testStart; // push start
    testStart.damage = 0;
    testStart.itemName = startVert->id;
    pq.insertElement(testStart);

    while(pq.peek() != nullptr){
        ItemInfo *front = pq.peek(); // extracting best
        string currentItem = front->itemName;
        pq.pop();

        Vertex *curr = vertices[currentItem];
        if(curr->solved){
            continue;
        }
        curr->solved = true;

        if(startVert == endVert){ // if reached end, done
            return endVert->distance;
        }
        for(auto &neighbor : curr->adjacent){ // "relaxing" edges
            Vertex *next = neighbor.v;
            string enemy = neighbor.enemy_id;

            node *enemyN = ht.searchCharacter(enemy);
            if (!enemyN){ // skipping for no weapons
                continue;
            }

            ItemInfo *strongestWeapon = enemyN->pq.peek();
            if (!strongestWeapon){
                continue;
            }
            int weight = strongestWeapon->damage;

            if(curr->distance + weight < next->distance){
                next->distance = curr->distance + weight;

                ItemInfo barf;
                barf.itemName = next->id;
                barf.damage = next->distance;

                pq.insertElement(barf);
            }

        }
    }
    return -1; // cant reach
}
