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
        std::cout << "line: " << line << std::endl;
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
          LinkedList<std::pair<int,int>> tmpList; // en ponderado lista de pares
          adjList[k] = tmpList; 
        }
      }
      else if (i > 0 && i <= numNodes) {
        ipAddress tmpIP(line, "", i);
        ips[i] = tmpIP;
        mapIP.insert({tmpIP.getIpValue(), tmpIP}); // {string ip, int}
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

void Graph::outDegrees(std::string fileName) {
  std::ofstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    for (int i = 1; i <= numNodes; i++) {
      file << "ip: " << ips[i].getIp() << "  grado: "  << ips[i].getDegree() << std::endl;
      maxHeapIPs.push(std::make_pair(ips[i].getDegree(), ips[i].getIp()));
    }
    file.close();
  }
}

void Graph::maxDegrees(std::string fileName) {
  std::ofstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    // get 5 ips
    for (int i = 1; i <= 5; i++) {
      std::pair<int, std::string> p = maxHeapIPs.top();
      maxHeapIPs.pop();
      file << "ip: " << p.second << "  grado: "  << p.first << std::endl;
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
/*
void Graph::printAdjMatrix(){
    std::cout << "Adjacency Matrix" << std::endl;
		for (int i = 1; i <= numNodes; i++){
	        std::cout << "vertex " << i << ": ";
	        for (int j = 1; j <= numNodes; j++){
							 std::cout << " " << adjMatrix[i][j];
					}
	        std::cout << std::endl;
    }
}

void Graph::printGraph() {
  if (representation == 1)
    printAdjList();
  else
    printAdjMatrix();
}

void Graph::BFS(int v) {
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Creamos una queue 
  QueueLinkedList<int> queue;
  // Marcamos el vertice actual v como visitado y entra al queue
  visited.insert(v);
  queue.enqueue(v);
  std::cout << "Recorrido BFS " << std::endl;
  while(!queue.isEmpty()) {
    // Extraemos un vertice del queue y lo procesamos (print) 
    v = queue.dequeue();
    std::cout << v << " ";
    // Obtenemos los vertices adyacentes del vertice v
    // Si estos no han sido visitados entonces se marcan como visitados
    // y los metemos al queue
    if (representation == 1) { // Lista de adyacencia
      // Recorrer nodos adyacentes de v
      for (int j = 0; j < (int)adjList[v].getNumElements(); j ++) {
        int u = adjList[v].getData(j);
        // Verifica si u ya fue visitado en tiempo O(log n)
        bool isInVisited = visited.find(u) != visited.end();
        if (!isInVisited) {
          visited.insert(u);
          queue.enqueue(u);
        }
      }
    }
    else { // Matriz de adyacencia
      // Recorrer nodos adyacentes a v
      for (int u = 1; u <= numNodes; u++) {
        int c = adjMatrix[v][u];
        if (c != 0) {
          // Verifica si u ya fue visitado en tiempo O(log n)
          bool isInVisited = visited.find(u) != visited.end();
          if (!isInVisited) {
            visited.insert(u);
            queue.enqueue(u);
          }
        }
      }
    }
  }
  std::cout << std::endl;
}

void Graph::DFS(int v) {
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Creamos un stack 
  StackLinkedList<int> stack;
  // Marcamos el vertice actual v como visitado y entra al queue
  visited.insert(v);
  stack.push(v);
  std::cout << "Recorrido DFS " << std::endl;
  while(!stack.isEmpty()) {
    // Extraemos un vertice del queue y lo procesamos (print) 
    v = stack.getTop(); 
    stack.pop();
    std::cout << v << " ";
    // Obtenemos los vertices adyacentes del vertice v
    // Si estos no han sido visitados entonces se marcan como visitados
    // y los metemos al queue
    if (representation == 1) { // Lista de adyacencia
      // Recorrer nodos adyacentes de v
      for (int j = 0; j < (int)adjList[v].getNumElements(); j ++) {
        int u = adjList[v].getData(j);
        // Verifica si u ya fue visitado en tiempo O(log n)
        bool isInVisited = visited.find(u) != visited.end();
        if (!isInVisited) {
          visited.insert(u);
          stack.push(u);
        }
      }
    }
    else { // Matriz de adyacencia
      // Recorrer nodos adyacentes a v
      for (int u = 1; u <= numNodes; u++) {
        int c = adjMatrix[v][u];
        if (c != 0) {
          // Verifica si u ya fue visitado en tiempo O(log n)
          bool isInVisited = visited.find(u) != visited.end();
          if (!isInVisited) {
            visited.insert(u);
            stack.push(u);
          }
        }
      }
    }
  }
  std::cout << std::endl;
}
*/