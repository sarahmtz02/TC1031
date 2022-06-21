/** 
* 
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/

#include <iostream>
#include "Bitacora.h"

using std::cout;
using std::endl;

//Main
int main () {
  
  Bitacora miBitacora("bitacoraHeap.txt");
  //miBitacora.print();
  //std::cout << "Bitacora ordenada" << std::endl;

  // probar para reflexion quicksort y heapsort
  //miBitacora.callQuickSort();
  miBitacora.heapSort();

  miBitacora.printToFile("bitacora_ordenada.txt");

  miBitacora.cuentaRepetidos("ips_con_mayor_acceso.txt");
  
  
  return 0;
}
