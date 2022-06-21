#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include "Registro.h"
#include "MaxHeap.h"
#include "mhPair.h"

class Bitacora {

  private:
    std::vector<Registro> listaRegistros;
    // declarar un maxHeap
    MaxHeap<mhPair> myMaxHeap;
    int partition(int low, int high);
    void quickSort(int low, int high);

  public:
    Bitacora();
    Bitacora(std::string fileName);
    void print();

    // Ordenamiento
    void bubbleSort();
    void callQuickSort();
    void printToFile(std::string fileName);
    void heapify(int n, int i);
    void heapSort();
    void cuentaRepetidos(std::string fileName);

      
    

};



#endif  // _BITACORA_H_