#include <iostream>
#include "Bitacora.h"

using std::cout;
using std::endl;

//Main
int main () {
  
  Bitacora miBitacora("bitacora.txt");
  //miBitacora.print();
  //std::cout << "Bitacora ordenada" << std::endl;
  //miBitacora.bubbleSort();
  miBitacora.sort();
  miBitacora.printToFile("bitacora_ordenada.txt");
  miBitacora.pideInfo();
  
  
  return 0;
}
