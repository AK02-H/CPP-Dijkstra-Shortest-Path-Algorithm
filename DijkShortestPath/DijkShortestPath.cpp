// Dijkstra's shortest path.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Extra pre-typed graph to test with: (copy and paste)
//map<char, map<char, int>> graph = {
//        {'A', { {'B', 7}, {'C', 9}, {'F', 14}  } },
//        {'C', { {'A', 9}, {'B', 10}, {'D', 11}, {'F', 2}  } },
//        {'B', { {'A', 7}, {'C', 10} , {'D', 15}  } },
//        {'D', { {'B', 15}, {'C', 11}, {'E', 6}  }},
//        {'E', { {'D', 6}, {'F', 9} }},
//        {'F', { {'A', 14}, {'C', 2}, {'E', 9} }}
//};



#include <iostream>
#include <map>
#include <limits>
#include <vector>

using namespace std;

//Node struct that stores distance and the node to get there from
struct nodePath {
    int dist = 0;
    char pathVia = NULL;

    nodePath();

    nodePath(int d, char pv) {
        dist = d;
        pathVia = pv;
    }

    

};

//Operator overload that allows outstreaming the node struct
ostream& operator<<(ostream& os, const nodePath n) {
    os << "{Distance: " << n.dist << ", PathVia: " << n.pathVia << "}" << endl;
   
    return os;
}

//utility function to check if a key is contained in a map
bool mapContains(map<char, nodePath> vMap, char item) {

    if (vMap.count(item)) {
        return true;
    }
    else {
        return false;
    }

}

//Returns the key in the map with the lowest distance
char getMinimum(map<char, nodePath> vMap) {
    int lowest = INT_MAX;
    char lowestKey = vMap.begin()->second.pathVia;
    cout << "LOWEST " << lowestKey << endl;


    for (auto item : vMap) {

        //cout << "minLoop" << endl;
        if (item.second.dist < lowest) {
            cout << "NEW LOWEST FOUND" << endl;
            lowest = item.second.dist; 
            lowestKey = item.first; 
        }
    }

    cout << "LOWEST " << lowestKey << endl;

    return lowestKey;
}

//Displays the shortest paths from the start node to every other node
void displayShortestPath(char start, map<char, nodePath> visited) {

    cout << "SHORTEST PATHS FROM NODE " << start << ": " << endl << endl;


    for (auto entry : visited) {

        auto key = entry.first;

        if (key != start) {
            char current = key;
            
            vector<char> path;

            path.push_back(current);

            cout << "PATH TO " << key << ": " << endl;

            //Backtrack with the pathVia keys until it reaches the start node
            while (current != start) {
                
                char previous = visited.find(current)->second.pathVia;
                path.push_back(previous);
                current = visited.find(current)->second.pathVia;       
            }
            
            for (auto k : path) {
                cout << k << " ";
            }
            cout << endl;

            cout << " Cost: " << visited.find(key)->second.dist << endl << endl;

        }
    }

}

//Main algorithm
int main()
{


    //Graph
    map<char, map<char, int>> graph = {
        {'A', { {'B', 8}, {'C', 5}  }},
        {'C', { {'A', 5}, {'D', 6}, {'E', 9}  }},
        {'B', { {'A', 8}, {'D', 1}  }},
        {'D', { {'C', 6}, {'B', 1}, {'E', 2}  }},
        {'E', { {'C', 9}, {'D', 2}  }}
    };



    char startNode = 'A';
    char currentNode = 'A';

    //Create lists to store which nodes have been visited or not, along with the distance to them and the node path to reach them from (as maps)
    map<char, nodePath> visited = {};
    map<char, nodePath> unvisited = {};




  
    
    //Initialises nodes
    for (const auto entry : graph) {
        auto k = entry.first;
        cout << k << endl;
        nodePath newNode(INT_MAX, NULL);    //set infinite distance and null for pathVia
        unvisited.insert({ k, newNode });
    }
    
    unvisited.find(startNode)->second.dist = 0; //set distance from start node to start node as 0

    bool finished = false;

    while (!finished) {

        //Do while there are still unvisited nodes
        if (unvisited.size() == 0) {
            finished = true;
        }
        else {

            currentNode = getMinimum(unvisited);
            for (auto neighbour : graph[currentNode]) { //foreach neighbour node of the current graph node

                if (!mapContains(visited, neighbour.first)) {   //if this node is not visited
                    //get cumalitive weight of edges to current node added to weight cost to current neighbour
                    int cost = unvisited.find(currentNode)->second.dist + graph.find(currentNode)->second.find(neighbour.first)->second;

                    //if path is shorter than the current distance to the neighbour, define new cost as the new shortest path to the node
                    //and mark down the node the path comes from
                    if (cost < unvisited.find(neighbour.first)->second.dist) {
                        unvisited.find(neighbour.first)->second.dist = cost;
                        unvisited.find(neighbour.first)->second.pathVia = currentNode;
                    }

                }
            }

            //Move node from unvisited list to visited list
            nodePath newNd(unvisited.find(currentNode)->second.dist, unvisited.find(currentNode)->second.pathVia);
            visited.insert({ currentNode, newNd });
            unvisited.erase(currentNode);   
        }

    }

    //Display shortest path
    displayShortestPath(startNode, visited);


}
