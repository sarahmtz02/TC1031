#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"
#include "DLinkedList.h"

class Bitacora {

  private:
    DLinkedList<Registro> listaRegistros;
    void printResultToFile(std::string fileName, DLLNode<Registro> *ini, DLLNode<Registro> *fin );
    

  public:
    Bitacora();
    Bitacora(std::string fileName);
    void print();

    // Ordenamiento
     
    void sort();
    void pideInfo();
    void printToFile(std::string fileName);

      
    

};



#endif  // _BITACORA_H_