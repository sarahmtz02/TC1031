#include clasificacion.h

void clasificacion::secondBucketSort(std::vector<bitacora>& array) {
	int n = array.size(), l = 0;
	for (int i = 0; i < 60; i++) {
		int p = 0;
		while (p < n){

			if (array[p].s == i) {

				swap(array, l, p);
				l++;
			}
			p++;
		}
	}
}

std::vector<bitacora> clasificacion::minuteBucketSort(std::vector<bitacora> array) {
	int n = array.size(), l = 0;
	std::vector<bitacora> sorted;
	for (int i = 0; i < 60; i++) {
		int p = 0;
		while (p < n and l < n) {
			if (array[p].m == i) {
				//swap(array, l, p);
				sorted.push_back(array[p]);
				l++;	
			}
			p++;
		}
	}
	return sorted;
}

std::vector<bitacora>clasificacion::hourBucketSort(std::vector<bitacora> array) {
	int n = array.size(), l = 0;
	std::vector<bitacora> sorted;
	for (int i = 0; i < 24; i++) {
		int p = 0;
		while (p < n) {
			if (array[p].h == i) {
				//swap(array, l, p);
				sorted.push_back(array[p]);
				l++;
			}
			p++;
		}
	}
	return sorted;
}

std::vector<bitacora> clasificacion::dayBucketSort(std::vector<bitacora> array) {
	int n = array.size(), l = 0;
	std::vector<bitacora> sorted;
	for (int i = 1; i < 32; i++) {
		int p = 0;
		while (p < n) {
			if (array[p].getDia() == i) {
				//swap(array, l, p);
				sorted.push_back(array[p]);
				l++;
			}
			p++;
		}
	}
	return sorted;
}

std::vector<bitacora> clasificacion::monthBucketSort(std::vector<bitacora> array) {
	int n = array.size(), l = 0;
	std::vector<bitacora> sorted;
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
	//this data set only contains months from june to october, so min can be set to 6 and max to 10. This makes it even faster.
	//if the data set where to have different dates, a little change would have to be implemented.
	int min_to_search = 6, max_to_search = 10;
	
	for (int i = min_to_search; i < max_to_search+1; i++) {
		int p = 0;
		std::cout << 75+(i*100/ max_to_search)*25/100 << "%\n";
		if (l == n-1) {
			break;
		}
		while (p < n) {
			if (MONTH_NUM[array[p].getMes()] == i) {
				//swap(array, l, p);
				sorted.push_back(array[p]);
				l++;
			}
			p++;
		}
	}
	return sorted;
}

void sort::fullBucketSort(std::vector<bitacora>& array) {
	std::cout << "CARGANDO...\n";
	secondBucketSort(array);
	std::cout << "0%\n";
	array = minuteBucketSort(array);
	std::cout << "25%\n";
	array = hourBucketSort(array);
	std::cout << "50%\n";
	array = dayBucketSort(array);
	std::cout << "75%\n";
	array = monthBucketSort(array);
}

void sort::swap(std::vector<bitacora>& array, int i, int j) {
	bitacora temp = array[i]; 
	array[i] = array[j];
	array[j] = temp;
}