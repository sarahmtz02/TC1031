#include "Graph.h"


Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
}

Graph::~Graph() {
  adjList.clear();
}

void Graph::loadGraphList(std::string fileName) {
  std::string line, month, day, hours, minutes, seconds, ipAdd, port, error;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    int i = 0;
    while (!file.eof()) {
      if (i == 0) {
        std::getline(file, line)
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[2];
        std::cout << "numNodes " << numNodes << std::endl;
        std::cout << "numEdges " << numEdges << std::endl;
        // Reservar memoria para los renglones de la lista de adyacencia (renglon 0 no utilizado) 
        adjList.resize(numNodes+1);
        // Declara una lista vacia para cada renglon y la almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          LinkedList<int> tmpList; // en ponderado lista de pares
          adjList[k] = tmpList; 
        }
        i++;
        continue;
      }
      if (i > 0 && i < numNodes) {
        std::getline(file, line)
        mapIP.insert({line, i});
        std::cout << "i: " << i << " IP: " << line << std::endl;
        i++;
        continue;
      }
      /*
        std::getline(file, month, ' ');
        std::getline(file, day, ' ');
        std::getline(file, hours, ':');
        std::getline(file, minutes, ':');
        std::getline(file, seconds, ' ');
        std::getline(file, ipAdd, ':');
        std::getline(file, port, ' ');
        std::getline(file, error);

      
        int u = res[0];
        int v = res[1];
        adjList[u].addLast({});
      */
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
/*
void Graph::printAdjList(){
	  std::cout << "Adjacency List" << std::endl;
		for (int i = 1; i <= numNodes; i++){
	        std::cout << "vertex " << i << ": ";
	        adjList[i].printList();
    }
}

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