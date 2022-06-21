#include "Bitacora.h"

//Constructor
Bitacora::Bitacora() {

}

//Agregando metodos de graph para cargar los archivos
Bitacora::Bitacora(std::string fileName) {
  graph.loadGraphList(fileName);
  graph.saveDegrees("grados_ips.txt");
  graph.saveTop("mayores_grados_ips.txt");
  graph.shortestPath("distancia_bootmaster.txt");

}

//Destructor
Bitacora::~Bitacora() {

}

