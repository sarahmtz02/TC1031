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
  for (int i=0; i < listaRegistros.size(); i++) {
    myOutFile << listaRegistros[i].getAll() << std::endl;
  }
  myOutFile.close();
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

int Bitacora::binarySearch(Registro k) {
  int low = 0;
  int high = listaRegistros.size() - 1;
  while (low <= high) {
    int m = low + (high - low) / 2;
    if (k == listaRegistros[m]) return m;
    else if (k < listaRegistros[m]) 
      high = m - 1;
    else 
      low = m + 1;
  }
  return -1;
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
    int inicio = binarySearch(iniRegistro);
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
    int fin = binarySearch(finRegistro);
    //std::cout << "Fin: " << fin << std::endl;

    if (inicio != -1 && fin != -1 && inicio < fin) {
      // Imprime
      std::cout << "\nEl resultado de la búsqueda es: " << std::endl;
      for (int i = inicio; i <= fin; i++) {
        std::cout << listaRegistros[i].getAll() << std::endl;
      }
    }
    else {
      std::cout << "La fecha de inicio o fin no son válidas" << std::endl;
    }
}