#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <assert.h>
#include <string>
#include <map>

class bitacora
{
public:
    
    //El constructor por default todo vacio 
    bitacora();
    //El constructor que le define los atributos del objeto.
    bitacora(std::string MES, std::string DIA = 0, std::string HORA = "", std::string IP = "", std::string RAZON_DE_FALLA = "") : mes(MES), dia(DIA), hora(HORA), ip(IP), RazonDeFalla(RAZON_DE_FALLA) {};

    void describe(); //Muestra los atributos del objeto
    void describeRaw(); //Muestra los atributos del objeto sin espaciado

    //Define una acción a seguir cuando se utilize un operador ostream en el objeto.
    friend std::ostream& operator << (std::ostream& out, const bitacora& obj);

    //Define una acción a seguir cuando se utilize un operador istream en el objeto.
    friend std::istream& operator >> (std::istream& in, bitacora& obj);

    // Convierte un string en un vector de numeros enteros
    std::vector<int> split(std::string str, char pattern);

    // Convierte un string de la forma hh:mm:ss en un unico numero entero representando los segundos
    void timeToInt();
    int getDia() {
        return this->dia;
    }
    std::string getMes() { 
        return mes;
    }
private:
    int h, m, s;
    std::string mes, dia, hora, ip, puerto, RazonDeFalla;

};
