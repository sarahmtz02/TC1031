#include "Bitacora.h"


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
        // Agregar a la DLinkedList de registros
        listaRegistros.addLast(tmpRegistro);
      }
  }
}

void Bitacora::print() {
  std::cout << "La bitacora contiene lo siguiente:" << std::endl;
  DLLNode<Registro> *ptr = listaRegistros.getHead();
  while (ptr != nullptr) {
    std::cout << ptr->data.getAll() << " ";
    ptr = ptr->next;
  }
}

void Bitacora::printToFile(std::string fileName) {
  std::ofstream myOutFile(fileName);
  DLLNode<Registro> *ptr = listaRegistros.getHead();
  while (ptr != nullptr) {
    myOutFile << ptr->data.getAll() << std::endl;
    ptr = ptr->next;
  }
  myOutFile.close();
}

void Bitacora::printResultToFile(std::string fileName, DLLNode<Registro> *ini, DLLNode<Registro> *fin) {
  std::ofstream myOutFile(fileName);
  DLLNode<Registro> *p, *q;
  p = ini;
  while (p != nullptr) {
    q = p->next;
    myOutFile << p->data.getAll() << std::endl;
    std::cout << p->data.getAll() << std::endl;
    p = q;
    if (p == fin->next) 
      break;
  }
  myOutFile.close();
}

void Bitacora::sort() {
  listaRegistros.callQuickSort();
}

void Bitacora::pideInfo() {
    std::string fecha;
    std::cout<<"Fecha inicial de los registros siguiendo el formato MMM DD HH:MM:SS "<<std::endl;
    getline(std::cin,fecha);
    std::string mes = fecha.substr(0, 3);
    std::string dia = fecha.substr(4, 2);
    std::string horas = fecha.substr(7, 2);
    std::string minutos = fecha.substr(10, 2);
    std::string segundos = fecha.substr(13, 2);
    // Crear un objeto de la clase Registro
    Registro iniRegistro(mes, dia, horas, minutos, segundos, "", "", "");
    // buscar fecha ini
    DLLNode<Registro> *inicio = listaRegistros.binarySearch(iniRegistro);
    //std::cout << "Inicio: " << inicio << std::endl;

    std::cout<<"Fecha final de los registros siguiendo el formato MMM DD HH:MM:SS "<<std::endl;
    getline(std::cin,fecha);
    mes = fecha.substr(0, 3);
    dia = fecha.substr(4, 2);
    horas = fecha.substr(7, 2);
    minutos = fecha.substr(10, 2);
    segundos = fecha.substr(13, 2);
    // Crear un objeto de la clase Registro
    Registro finRegistro(mes, dia, horas, minutos, segundos, "", "", "");
    // buscar fecha ini
    DLLNode<Registro> *fin = listaRegistros.binarySearch(finRegistro);
    //std::cout << "Fin: " << fin << std::endl;

    if (inicio != nullptr && fin != nullptr) {
      // Imprime
      std::cout << "\nEl resultado de la búsqueda es: " << std::endl;
      printResultToFile("resultado_busqueda.txt", inicio, fin);
    }
    else {
      std::cout << "La fecha de inicio o fin no son válidas" << std::endl;
    }
}