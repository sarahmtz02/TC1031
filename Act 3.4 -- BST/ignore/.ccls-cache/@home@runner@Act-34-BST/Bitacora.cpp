#include "Bitacora.h"
#include <queue>


Bitacora::Bitacora() {
  
}

Bitacora::Bitacora(std::string fileName) {
  std::string month, day, hours, minutes, seconds, ipAdd, port, error;
  
  //PARA LEER LOS ARCHIVOS USAR CLASE IFSTREAM
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while (!file.eof()) {
        // Sep 23 12:58:18 80.169.79.65:1150 Failed password
        std::getline(file, month, ' ');
        std::getline(file, day, ' ');
        std::getline(file, hours, ':');
        std::getline(file, minutes, ':');
        std::getline(file, seconds, ' ');
        std::getline(file, ipAdd, ':');
        std::getline(file, port, ' ');
        std::getline(file, error);
        // Crear un objeto de la clase Registro
        Registro tmpRegistro(month, day, hours, minutes, seconds, ipAdd, port, error);
        // Agregar al vector de registros
        listaRegistros.push_back(tmpRegistro);
      }
  }
}

void Bitacora::print() {
  std::cout << "La bitacora contiene lo siguiente:" << std::endl;
  for (int i=0; i < listaRegistros.size(); i++)
    std::cout << listaRegistros[i].getAll() << std::endl;
}

void Bitacora::printToFile(std::string fileName) {
  std::ofstream myOutFile(fileName);
  if (!myOutFile.good()) {
    myOutFile.close();
    throw std::invalid_argument("File not found");
  }
  else {  
    for (int i=0; i < listaRegistros.size(); i++) {
      myOutFile << listaRegistros[i].getAll() << std::endl;
    }
    myOutFile.close();
  }
}

int Bitacora::partition(int low, int high) {
  Registro pivot = listaRegistros[high];
  int i = low-1;
  for(int j = low; j<high; j++) {
    if(listaRegistros[j] < pivot){
      i++;
      Registro temp = listaRegistros[i];
      listaRegistros[i] = listaRegistros[j];
      listaRegistros[j] = temp;
    }
  }
  Registro temp2 = listaRegistros[i+1];
  listaRegistros[i+1] = listaRegistros[high];
  listaRegistros[high] = temp2;
  return i+1;
}

void Bitacora::quickSort(int low, int high) {
  if (low < high)  {
    // encontrar pivote de la particion
	  int pi = partition(low, high);
    // ordenar la mitad izquierda y derecha
	  quickSort(low, pi - 1);
	  quickSort(pi + 1, high);
  }
}

void Bitacora::callQuickSort() {
  quickSort(0, listaRegistros.size()-1);
}

void Bitacora::heapify(int n, int i) {
  // Initialize largest as root
  int largest = i;
  // left = 2*i + 1
  int l = 2 * i + 1; 
  // right = 2*i + 2
  int r = 2 * i + 2;
  // If left child is larger than root
  if (l < n && listaRegistros[l] > listaRegistros[largest])
    largest = l;
  // If right child is larger than largest so far
  if (r < n && listaRegistros[r] > listaRegistros[largest])
    largest = r;
  // If largest is not root
  if (largest != i) {
    std::swap(listaRegistros[i], listaRegistros[largest]);
    // Recursively heapify the affected sub-tree
    heapify(n, largest);
  }
}

void Bitacora::heapSort() {
  int n = listaRegistros.size();
  // Build heap (rearrange array)
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(n, i);
  // One by one extract an element from heap
  for (int i = n - 1; i > 0; i--) {
    // Move current root to end
    std::swap(listaRegistros[0], listaRegistros[i]);
    // call max heapify on the reduced heap
    heapify(i, 0);
  }
}

void Bitacora::cuentaRepetidos(std::string fileName) {
  std::map<std::string, int> dups;
  for (int i = 0; i < listaRegistros.size(); i++) {
    ++dups[listaRegistros[i].getIP()];
  }
  // max heap para recuperar las 5 IPs con mayor numero de accesos
  myMaxHeap.setCapacity(listaRegistros.size());
  for(auto& dup : dups) {
      mhPair myPair(dup.second, dup.first); 
      myMaxHeap.push(myPair);
  }

  // Aqui hacer un for para consultar con top las 5 IPs con mayor numero de accesos
  std::ofstream myOutFile(fileName);
  if (!myOutFile.good()) {
    myOutFile.close();
    throw std::invalid_argument("File not found");
  }
  else{
    for(int j = 1; j <= 5; j++){
      mhPair myPair = myMaxHeap.top();
      std::cout << "El max es: " << myPair.getIP() << " con " << myPair.getAccesos() << " accesos" << std::endl;
      myOutFile << "El max es: " << myPair.getIP() << " con " << myPair.getAccesos() << " accesos" << std::endl;
      myMaxHeap.pop();
    }
    myOutFile.close();  
  } 
}


