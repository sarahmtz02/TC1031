#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <vector>
#include <string>
#include "LinkedList.h"

class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia (vector de listas)
    std::vector<LinkedList<std::pair<int,int>>> adjList;
    // mapea IPs a un numero entero de orden
    std::map<std::string, >

    void loadGraphList(std::istream& input);
    void split(std::string line, std::vector<int> & res);
  
  public:
    Graph(int representacion, std::istream& input);
    ~Graph();
    void printGraph();
    
};




#endif // __GRAPH_H_