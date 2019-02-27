#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

constexpr int file_size = 1085;
constexpr int days_amount = 255;


struct date_t {
	std::string date_str;
	short guard_num;
	bool hour_sleep[60] = {};
};

int search_in_vector(std::vector<int> vec, int num) {
	unsigned int vec_size = vec.size();

	for (int i = 0; i < vec_size; i++) {
		if (vec[i] == num) return i;
	}
	return -1;
}

int compare_dates(const void *first, const void *second) {
	if (*(std::string*)first < *(std::string*)second) return -1;
	if (*(std::string*)first == *(std::string*)second) return 0;
	if (*(std::string*)first > *(std::string*)second) return 1;
}

int main() {

	std::fstream file;
	file.open("plik.txt", std::ios::in);
	if (!file.is_open()) std::cout << "file error\n";

	std::string notes[file_size];

	for (int i = 0; i < file_size; i++) {
		std::getline(file, notes[i]);		//odczyt linii do stringów
	}

	size_t string_size = 0;

	for (int i = 0; i < file_size; i++) {  //pobranie jednakowej d³ugoœci dla stringów
		if (notes[i].size() > string_size)
			string_size = notes[i].size();
	}

	for (int i = 0; i < file_size; i++) {  //ustawienie wspólnej d³ugoœci stringów notek z dziennika
		notes[i].resize(string_size, ' ');
	}

	qsort(notes, file_size, sizeof(notes[0]), &compare_dates); //posortowanie stringów chronologicznie


	date_t dates[days_amount];
	int string_ptr = 0;
	int day_index = 0;
	int number_day_index = 0;
	int pos_ptr = 26;
	int pos_ptr2 = 0;
	int pos_ptr3 = 15;
	int minute;
	std::string copy_strGuard;
	copy_strGuard.resize(4);   //zmienne potrzebne do wczytywania
	char copy_str[10] = "0";

	while (day_index < days_amount && string_ptr < file_size) {
		if (notes[string_ptr].find('#') != std::string::npos) { //gdy znajdzie numer stra¿nika


			if (string_ptr && day_index < days_amount - 1) day_index++;	//warunek prawid³owego odliczania dnia

			while (notes[string_ptr][pos_ptr] != ' ') {  //wczytanie stringa z numerem stra¿nika
				copy_strGuard[pos_ptr2] = notes[string_ptr][pos_ptr];
				pos_ptr++;
				pos_ptr2++;
			}
			dates[day_index].guard_num = std::stoi(copy_strGuard);

			copy_strGuard.clear();
			copy_strGuard.resize(4);
			pos_ptr = 26;
			pos_ptr2 = 0;			//przywrócenie zmiennych na wart. pocz.

			if (notes[string_ptr][12] == '2') {  //gdy zaczyna zmianê przed pó³noc¹
				notes[string_ptr + 1].copy(copy_str, 10, 1);
				dates[day_index].date_str = copy_str;	//kopiowanie stringa z dat¹ nastêpnego dnia 
			}
			else {		//gdy zaczyna zmianê po pó³nocy
				notes[string_ptr].copy(copy_str, 10, 1);
				dates[day_index].date_str = copy_str;	//kopiowanie stringa z dat¹ tego dnia 
			}
			string_ptr++;
		}
		else {		//informacja o œnie lub pobudce
			if (notes[string_ptr][19] == 'f') {
				while (notes[string_ptr][pos_ptr3] != ']') {
					copy_strGuard[pos_ptr2] = notes[string_ptr][pos_ptr3];
					pos_ptr3++;
					pos_ptr2++;
				}
				minute = std::stoi(copy_strGuard);

				copy_strGuard.clear();
				copy_strGuard.resize(4);
				pos_ptr3 = 15;
				pos_ptr2 = 0;

				for (int a = minute; a < 60; a++) {
					dates[day_index].hour_sleep[a] = true;		//ustawienie snu w dzienniku
				}
			}
			else if (notes[string_ptr][19] == 'w') {
				while (notes[string_ptr][pos_ptr3] != ']') {
					copy_strGuard[pos_ptr2] = notes[string_ptr][pos_ptr3];
					pos_ptr3++;
					pos_ptr2++;
				}
				minute = std::stoi(copy_strGuard);

				copy_strGuard.clear();
				copy_strGuard.resize(4);
				pos_ptr3 = 15;
				pos_ptr2 = 0;

				for (int a = minute; a < 60; a++) {
					dates[day_index].hour_sleep[a] = false;
				}
			}
			string_ptr++;
		}
	}

	///znalezienie guarda

	std::vector<int> Vec;

	for (int i = 0; i < days_amount; i++) {
		if (search_in_vector(Vec, dates[i].guard_num) == -1) {
			Vec.push_back(dates[i].guard_num);
		}
	}

	std::vector<int> int_ptr;
	int_ptr.resize(Vec.size(), 0);

	int index = -1;

	for (int i = 0; i < days_amount; i++) {
		index = search_in_vector(Vec, dates[i].guard_num);

		for (int j = 0; j < 60; j++) {
			if (dates[i].hour_sleep) int_ptr[index]++;
		}
	}

	int most_Guard = 0;
	int index_most_Guard;

	for (int i = 0; i < Vec.size(); i++) {
		if (int_ptr[i] >= most_Guard) {
			most_Guard = int_ptr[i];
			index_most_Guard = i;
		}
	}

	int arr[60] = {};

	for (int i = 0; i < days_amount; i++) {
		if (dates[i].guard_num == Vec[index_most_Guard]) {
			for (int j = 0; j < 60; j++) {
				if (dates[i].hour_sleep[j]) arr[j]++;
			}
		}
	}

	int most_hours = 0;
	int index_most_hours;

	for (int i = 0; i < 60; i++) {
		if (arr[i] > most_hours) {
			most_hours = arr[i];
			index_most_hours = i;
		}
	}

	std::cout << Vec[index_most_Guard] * index_most_hours << std::endl;
}