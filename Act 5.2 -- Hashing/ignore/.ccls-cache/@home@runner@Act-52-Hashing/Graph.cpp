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
        ips[ip1Index].addToDegree(); // arista saliente
        ips[ip2Index].addToDegreeIn(); // arista entrante
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

void Graph::fillHashTable() {
  // 13370 * 1.3 = 17381 --> mover al primo mas cercano 17383
  // alfa = 13370 / 17383 = 0.77 --- Factor de carga
  // tableH.setCapacity(17383); // Collisions: 8804
  // 13370 * 2.1 = 28077 --> mover al primo mas cercano 28081
  // alfa = 13370 / 28081 = 0.48  --- Factor de carga
  tableH.setCapacity(28081); // Collisions: 2093
  std::cout << "Llenando tabla hash de capacidad maxima: " << tableH.getMaxSize() << std::endl;
  for (int i = 1; i < ips.size(); i++) {
    tableH.add(ips[i].getIpValue(), ips[i]);
  }
  std::cout << "Tabla hash size: " << tableH.getSize() << std::endl;
  std::cout << "Collisions: " << tableH.getCollisions() << std::endl;
}

void Graph::getIPSummary() {
  std::string ipStr;
  std::cout << "Dame una IP:" << std::endl;
  std::cin >> ipStr;
  ipAddress ipAdd(ipStr, "", 0);
  ipAddress resultIP = tableH.find(ipAdd.getIpValue());

  std::cout << std::endl;
  std::cout << "IP: " << resultIP.getIp() << std::endl;
  std::cout << "Direcciones accesadas desde la IP: " << resultIP.getDegree() << std::endl;
  std::cout << "Direcciones que accesan a la IP: " << resultIP.getDegreeIn() << std::endl;
   
  std::vector<ipAddress> listaIPs;
  int u = resultIP.getIpIndex();
  for (int j = 0; j < adjList[u].getNumElements(); j++) {
    std::pair<int, int> p = adjList[u].getData(j);
    listaIPs.push_back(ips[p.first]);
  }
  // ordenar vector usando algoritmo introsort  https://en.wikipedia.org/wiki/Introsort
  std::sort(listaIPs.begin(), listaIPs.end());
  std::cout << "Direcciones accessadas desde la IP: " << std::endl;
  for (int i = 0; i < listaIPs.size(); i++){
    std::cout << listaIPs[i].getIp() << std::endl;
  }
  
}



