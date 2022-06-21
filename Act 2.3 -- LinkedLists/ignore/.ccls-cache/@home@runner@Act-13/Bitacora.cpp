#include "Bitacora.h"


Bitacora::Bitacora() {
  
}

Bitacora::Bitacora(std::string fileName) {
  std::string month, day, hours, minutes, seconds, ipAdd, port, error;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while (!file.eof()) {
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
        // Agregar al vector de regisrros
        listaRegistros.push_back(tmpRegistro);
      }
  }
}

void Bitacora::print() {
  std::cout << "La bitacora contiene lo siguiente:" << std::endl;
  for (int i=0; i < listaRegistros.size(); i++)
    std::cout << listaRegistros[i].getAll() << std::endl;
}

void Bitacora::bubbleSort() {
  int i, j;
  int n = listaRegistros.size();
  Registro tmp;
  for (i = 0; i < n-1; i++) {
    for (j = 0; j < n-i-1; j++) {
      if (listaRegistros[j] > listaRegistros[j+1]){
        tmp = listaRegistros[j];
        listaRegistros[j] = listaRegistros[j+1];
        listaRegistros[j+1] = tmp;
      }
    }
  }
}

