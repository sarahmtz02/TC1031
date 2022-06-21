#ifndef _REGISTRO_H_
#define _REGISTRO_H_


#include <ctime>
#include <iostream>
#include <vector>

class Registro
{
  public:
      //El constructor por default todo vacio 
      Registro();
      //El constructor que le define los atributos del objeto.
      Registro(std::string MES, std::string DIA, std::string HORA, std::string MINUTOS, std::string SEGUNDOS, std::string IP, std::string PUERTO, std::string RAZON_DE_FALLA );
      time_t getDate();
      std::string getAll();
      bool operator ==(const Registro&);
      bool operator !=(const Registro&);
      bool operator >(const Registro&);
      bool operator <(const Registro&);
      bool operator <=(const Registro&);
      bool operator >=(const Registro&);
  
  private:
      std::string mes, dia, hora, minutos, segundos, ip, puerto, RazonDeFalla;
      std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; 
      // Struct que contiene todos los datos de la fecha-hora
      struct tm dateStruct;
      // Unix timestamp (segundos transcurridos desde 00:00 hrs, Jan 1, 1970 UTC)
      time_t dateTime;
};


#endif  // _REGISTRO_H_