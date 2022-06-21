#include "Bitacora.h"

//Constructor
Bitacora::Bitacora() {

}

//Agregando metodos de graph para cargar los archivos
Bitacora::Bitacora(std::string fileName) {
  graph.loadGraphList(fileName);
  //graph.printGraph();
  graph.outDegrees("grados_ips.txt");
  graph.maxDegrees("mayores_grados_ips.txt");
}

//Destructor
Bitacora::~Bitacora() {

}

