
#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include "LinkedList.h"
#include "ipAddress.h"
#include "HashTable.h"



class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia (vector de listas de pares <nodoDest, peso>)
    std::vector<LinkedList<std::pair<int,int>>> adjList;
    // mapea IPs a un numero entero de orden
    std::map<unsigned int, ipAddress> mapIP;
    // vector de objetos ipAddress para contar los grados
    std::vector<ipAddress> ips;
    // Hash table < ipValue, ipAddress>
    HashTable<unsigned int, ipAddress> tableH;

    void split(std::string line, std::vector<int> & res);
  
  public:
    Graph();
    ~Graph();
    void loadGraphList(std::string fileName);
    void printGraph();
    void fillHashTable();
    void getIPSummary();
    
    
};




#endif // __GRAPH_H_