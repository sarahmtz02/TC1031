
#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include "LinkedList.h"
#include "ipAddress.h"

# define INF 0x3f3f3f3f 

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
    // maxHeap <grado, ipString>
    std::priority_queue<std::pair<int, std::string>> maxHeapIPs;
    // BootMaster
    std::string ipBootMaster;
    int nodoBootMaster;
    
    void split(std::string line, std::vector<int> & res);
  
  public:
    Graph();
    ~Graph();
    void loadGraphList(std::string fileName);
    void printGraph();
    void outDegrees(std::string fileName);
    void maxDegrees(std::string fileName);
    void shortestPath(int src);
    void saveDegrees(std::string fileName);
    void saveTop(std::string fileName);
    void shortestPath(std::string filename);
    
};




#endif // __GRAPH_H_