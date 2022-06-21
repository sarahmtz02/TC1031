#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"

class Bitacora {

  private:
    std::vector<Registro> listaRegistros;

  public:
    Bitacora();
    Bitacora(std::string fileName);
    void print();
    // Ordenamiento
    void bubbleSort();
    // Busqueda

};



#endif  // _BITACORA_H_