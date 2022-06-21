#include "log.h"


bitacora::biracora() {
  
}

//Atributos del objeto
void bitacora::describe() {
    std::cout << std::endl << std::setw(10) << std::left << mes << std::setw(10)
        << dia << std::setw(15) << hora << std::setw(22) << ip << RazonDeFalla << std::endl;   
}

void bitacora::describeRaw() {
    std::cout << std::endl << '*' << mes << '*'
        << dia << '*' << hora << '*' << ip << '*' << RazonDeFalla << std::endl;
}

//De string a un vecto de numeros enteros
std::vector<int> bitacora::split(std::string str, char pattern) {
    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<int> results;
    while (posFound >= 0) {
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(std::stoi(splitted));
    }
    return results;
}

//De string a hh:mm:ss en enteros
void bitacora::timeToInt() {
    std::vector<int> splittedHours = this->split(this->hora, ':');
    this->h = splittedHours[0]; this->m = splittedHours[1]; this->s = splittedHours[2];
}

//Accion segun el istream
std::istream& operator >> (std::istream& in, bitacora& obj) 
{         
    in >> obj.mes;
    in >> obj.dia;
    in >> obj.hora;
    in >> obj.ip;
    std::getline(in, obj.RazonDeFalla);
    obj.RazonDeFalla = obj.RazonDeFalla.substr(1);
    return in;
}

//Accion que se hara despues del ostream
std::ostream& operator << (std::ostream& out, const bitacora& obj){                                                                         
    out << std::endl << std::setw(10) << std::left << obj.mes << std::setw(10)
        << obj.dia << std::setw(15) << obj.hora << std::setw(22) << obj.ip << obj.RazonDeFalla;
    return out;
}
