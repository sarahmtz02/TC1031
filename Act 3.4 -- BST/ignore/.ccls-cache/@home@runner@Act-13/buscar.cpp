#include "buscar.h"

void buscar::MonthAndDaySearch(std::vector<bitacora>& array, std::string lowerMonth, std::string upperMonth, int lowerDay, int upperDay){
	std::map<std::string, int> MONTH_NUM = {
	{"Jan", 1},
	{"Feb", 2},
	{"Mar", 3},
	{"Apr", 4},
	{"May", 5},
	{"Jun", 6},
	{"Jul", 7},
	{"Aug", 8},
	{"Sep", 9},
	{"Oct", 10},
	{"Nov", 11},
	{"Dec", 12},
	};
	int lowerM = MONTH_NUM[lowerMonth], upperM = MONTH_NUM[upperMonth];
	bool resultados = false;
	for (int i = 0; i < array.size(); i++) {
		if ((MONTH_NUM[array[i].getMes()] >= lowerM && MONTH_NUM[array[i].getMes()] <= upperM) && (array[i].getDia() >= lowerDay && array[i].getDia() <= upperDay)) {
			std::cout << array[i];
			resultados = true;
		}
		if (MONTH_NUM[array[i].getMes()] > upperM) {
			break;
		}
		if ((MONTH_NUM[array[i].getMes()] >= lowerM && MONTH_NUM[array[i].getMes()] <= upperM) && array[i].getDia() > upperDay) {
			break;
		}
	}
	if (!resultados) {
		std::cout << "SIN RESULTADOS. ";
	}
	std::cout << "Busqueda terminada. \n\n";
}