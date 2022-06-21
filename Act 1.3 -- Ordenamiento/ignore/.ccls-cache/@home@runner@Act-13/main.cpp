#include <iostream>
#include "Registro.h"

using std::cout;
using std::endl;

//Main
int main () {
  Registro r1 ("Jun", "01", "10", "30", "20", "1.2.3.4", "5657", "La falla fue esta");
  
  cout << r1.getDate() << endl;

  Registro r2 ("Jun", "01", "10", "30", "21", "1.2.3.4", "5657", "La falla fue esta");
  
  cout << r2.getDate() << endl;

  if (r1 < r2)
      cout << " es menor " << endl;
  
  return 0;
}
