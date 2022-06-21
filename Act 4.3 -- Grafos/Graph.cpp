#include "Graph.h"


Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
}

Graph::~Graph() {
  adjList.clear();
  ips.clear();
}

void Graph::loadGraphList(std::string fileName) {
  std::string line, ip1, ip2, peso;
  int i = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while(std::getline(file,line)) {
      if (i == 0) {
        //std::cout << "line: " << line << std::endl;
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        //std::cout << "numNodes " << numNodes << std::endl;
        //std::cout << "numEdges " << numEdges << std::endl;
        // Reservar memoria para los renglones de la lista de adyacencia (renglon 0 no utilizado) 
        adjList.resize(numNodes+1);
        ips.resize(numNodes+1);
        // Declara una lista vacia para cada renglon y la almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          // Lista de adyacencia (vector de listas de pares <nodoDest, peso>)
          LinkedList<std::pair<int,int>> tmpList; // en ponderado lista de pares
          adjList[k] = tmpList; 
        }
      }
      else if (i > 0 && i <= numNodes) {
        ipAddress tmpIP(line, "", i);
        ips[i] = tmpIP;
        mapIP.insert({tmpIP.getIpValue(), tmpIP}); // {ipValue, ipAddress}
        //std::cout << "i: " << i << " IP: " << line << std::endl;
      } 
      else if (i > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found-15);
        std::size_t found2 = line.find(" ", found+1);
        std::size_t found3 = line.find(":", found2+1);
        ip2 = line.substr(found2, found3-found2);
        std::size_t found4 = line.find(" ", found3+1);
        std::size_t found5 = line.find(" ", found4+1);
        peso = line.substr(found4, found5-found4);
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, "", 0);
        ipAddress tmpIP2(ip2, "", 0);
        std::map<unsigned int, ipAddress>::iterator it;
        int ip1Index, ip2Index;
        it = mapIP.find(tmpIP1.getIpValue());     
        if(it != mapIP.end())
          ip1Index = it->second.getIpIndex();
        it = mapIP.find(tmpIP2.getIpValue());     
        if(it != mapIP.end())
          ip2Index = it->second.getIpIndex();
        adjList[ip1Index].addLast({ip2Index, stoi(peso)});
        ips[ip1Index].addToDegree();
      }
      i++;
    }
    file.close();
  }
}



void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::printGraph(){
	  std::cout << "Adjacency List" << std::endl;
		for (int u = 1; u <= numNodes; u++){
      std::cout << "vertex " << u << ": ";
      for (int j = 0; j < adjList[u].getNumElements(); j++) {
        std::pair<int, int> p = adjList[u].getData(j);
        std::cout << "{" << p.first << ", " << p.second << "} ";
      }
      std::cout << std::endl;
    }
}

void Graph::saveDegrees(std::string fileName) {
  std::ofstream myOutFile(fileName);
  if (!myOutFile.good()) {
    myOutFile.close();
    throw std::invalid_argument("File not found");
  }
  else{
    for (int i=1; i < ips.size(); i++) {
      myOutFile << ips[i].getIp() << " --> " << ips[i].getDegree() << std::endl;
      maxHeapIPs.push(std::make_pair(ips[i].getDegree(), ips[i].getIp()));
    }
    myOutFile.close();
  }
}

void Graph::saveTop(std::string fileName) {
  
  // Aqui hacer un for para consultar con top las 5 IPs con mayor numero de accesos
  std::ofstream myOutFile(fileName);
  if (!myOutFile.good()) {
    myOutFile.close();
    throw std::invalid_argument("File not found");
  }
  else{
    for(int j = 1; j <= 5; j++){
      std::pair<int, std::string> myPair = maxHeapIPs.top();
      std::cout << myPair.second << " con grado " << myPair.first << std::endl;
      myOutFile << myPair.second << " con grado " << myPair.first << std::endl;
      maxHeapIPs.pop();
      if (j == 1) {
        ipBootMaster = myPair.second;
        ipAddress tmpBM(ipBootMaster, "", 0);
        std::map<unsigned int, ipAddress>::iterator it;
        it = mapIP.find(tmpBM.getIpValue());     
        if(it != mapIP.end())
          nodoBootMaster = it->second.getIpIndex();
      }
    }
    myOutFile.close();
    std::cout << std::endl;
    std::cout << "El bootmaster es: " << ipBootMaster << std::endl;
    std::cout << "Se encuentra en el nodo: " << nodoBootMaster << std::endl;
  } 
}

void Graph::shortestPath(std::string filename) {
    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    std::priority_queue< std::pair<int,int>, std::vector<std::pair<int,int>> , std::greater<std::pair<int,int>> > pq;

    int src = nodoBootMaster;
    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    std::vector<int> dist(numNodes+1, INF);
 
    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(std::make_pair(0, src));  // par {distancia, nodo}
    dist[src] = 0;
 
    // Looping till priority queue becomes empty (or all distances are not finalized) 
    while (!pq.empty()) {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();
        // recupera los vecinos del nodo u
        for (int j = 0; j < adjList[u].getNumElements(); j++) {
            std::pair<int, int> p = adjList[u].getData(j);  
            int v = p.first;
            int weight = p.second;
            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight) {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }
 
    // Print shortest distances stored in dist[]
    std::ofstream myOutFile(filename);
    if (!myOutFile.good()) {
      myOutFile.close();
      throw std::invalid_argument("File not found");
    }
    else {
      myOutFile << "Shortest path" << std::endl;
      myOutFile << "Vertex\t\tDistance from Source" << std::endl;
      int maxDist = dist[1];
      int maxIndex = 1;
      for (int i = 1; i <= numNodes; i++){
        myOutFile << ips[i].getIp() << "\t\t" << dist[i] << std::endl;
        if (dist[i] > maxDist) {
          maxDist = dist[i];
          maxIndex = i;
        }
      }
      std::cout << std::endl;
      std::cout << "Distancia máxima: " << maxDist <<std::endl; 
      std::cout << "IP a distancia máxima: " << ips[maxIndex].getIp() << std::endl;
    
    }
    myOutFile.close();
}

  
