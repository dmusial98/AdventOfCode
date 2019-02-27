#include <iostream>
#include <string>
#include<fstream>

///UWAGA POWIEKSZYC STOS, BO PRZECIAZY PROGRAM////////////////////////////////////////////////////////////////////

constexpr int parts_amount = 1305;
constexpr int array_size = 1000;

struct fabric_t {
	int fir_left;
	int fir_top;
	int width;
	int height;
};

void read_file(fabric_t fab_ar[]) {
	std::fstream file;
	file.open("plik.txt", std::ios::in);
	if (!file.is_open()) std::cout << "file error\n";

	char in_char = 'a';
	std::string in_string;
	in_string.resize(3);
	int string_index = 0;
	int amount_digit = 0;

	std::string bufor;
	for (int i = 0; i < parts_amount; i++) {
		for (int j = 0; j < 3; j++) {
			file >> bufor;    //pomini�ce numeru cz�ci i znaku @
		}
		while (in_char != ',') { //wczytanie pierwszej wsp�rz�dnej
			in_string[string_index] = bufor[string_index];
			in_char = bufor[++string_index];
			amount_digit++;
		}
		fab_ar[i].fir_left = std::stoi(in_string);
		in_char = bufor[++string_index];
		in_string.clear();
		in_string.resize(3);

		while (in_char != ':') { //wczytanie drugiej wsp�rz�dnej
			in_string[string_index - amount_digit - 1] = bufor[string_index];
			in_char = bufor[++string_index];
		}
		fab_ar[i].fir_top = std::stoi(in_string);
		file >> bufor;
		string_index = 0;
		in_char = bufor[string_index];
		in_string.clear();
		in_string.resize(3);
		amount_digit = 0;

		while (in_char != 'x') { //wczytanie szeroko�ci
			in_string[string_index] = bufor[string_index];
			in_char = bufor[++string_index];
			amount_digit++;
		}
		fab_ar[i].width = std::stoi(in_string);
		in_char = bufor[++string_index];
		in_string.clear();
		in_string.resize(3);

		while (in_char >= '0' && in_char <= '9') { //wczytywanie wysoko�ci
			in_string[string_index - amount_digit - 1] = bufor[string_index];
			in_char = bufor[++string_index];
		}
		fab_ar[i].height = std::stoi(in_string);
		in_string.clear();
		in_string.resize(3);
		string_index = 0;
		amount_digit = 0;
	}
}

int main() {

	fabric_t fab_ar[parts_amount];

	read_file(fab_ar);

	short fab_ar2[array_size][array_size]; // tablica na naszej kawa�ki materia�u

	for (int i = 0; i < array_size; i++) {
		for (int j = 0; j < array_size; j++) {
			fab_ar2[i][j] = -1;				//domy�lne wype�nienie -1k�
		}
	}
	bool correct_ID[parts_amount] = {}; //tablica dla zaznaczenia kt�ra cz�� materia�u nie nachodzi, domy�lnie wype�niona zerami 
	for (int i = 0; i < parts_amount; i++) { //po wszystkich 1305 kawa�kach

		for (int a = fab_ar[i].fir_left; a < fab_ar[i].width + fab_ar[i].fir_left; a++) {
			for (int b = fab_ar[i].fir_top; b < fab_ar[i].height + fab_ar[i].fir_top; b++) {
				if (fab_ar2[a][b] == -1)
				fab_ar2[a][b] = i;					//wype�nianie swoim numerem

				else  {
					fab_ar2[a][b] = -100;			//gdy nast�puje kolizja
				}
			}
		}
	}
	
	for (int i = 0; i < parts_amount; i++) {
		for (int a = fab_ar[i].fir_left; a < fab_ar[i].width + fab_ar[i].fir_left; a++) {
			for (int b = fab_ar[i].fir_top; b < fab_ar[i].height + fab_ar[i].fir_top; b++) {
				if (fab_ar2[a][b] == -100)
					correct_ID[i] = true;		//odznaczenie, gdy cz�� materia�u nachodzi na inny
			}
		}
	}

	for (int i = 0; i < parts_amount; i++) {
		if (!correct_ID[i])
			std::cout << i+1<< std::endl;		//wy�wietlenie wyniku 
	}
}