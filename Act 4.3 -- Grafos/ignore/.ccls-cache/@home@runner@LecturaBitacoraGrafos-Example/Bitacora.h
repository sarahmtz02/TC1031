#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Graph.h"

class Bitacora {

  private:
    Graph graph; //Declarando un objeto grafo

  public:
    Bitacora(); //Constructor
    Bitacora(std::string fileName); //lectura de archivo
    ~Bitacora(); //Destructor

};



#endif  // _BITACORA_H_