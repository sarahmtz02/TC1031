#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Registro.h"

class Bitacora {

  private:
    std::vector<Registro> listaRegistros;
    int partition(int low, int high);
    void quickSort(int low, int high);

  public:
    Bitacora();
    Bitacora(std::string fileName);
    void print();

    // Ordenamiento
    void bubbleSort();
    void callQuickSort();
    int binarySearch(Registro k);
    void pideInfo();
    void printToFile(std::string fileName);

      
    

};



#endif  // _BITACORA_H_