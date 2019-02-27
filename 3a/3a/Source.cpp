#include <iostream>
#include <string>
#include<fstream>

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
			file >> bufor;    //pominiêce numeru czêœci i znaku @
		}	
		while (in_char != ',') { //wczytanie pierwszej wspó³rzêdnej
			in_string[string_index] = bufor[string_index];
			in_char = bufor[++string_index];
			amount_digit++;
		}  
			fab_ar[i].fir_left = std::stoi(in_string);
			in_char = bufor[++string_index];
			in_string.clear();
			in_string.resize(3);

		while (in_char != ':') { //wczytanie drugiej wspó³rzêdnej
			in_string[string_index -amount_digit -1] = bufor[string_index];
			in_char = bufor[++string_index];
		} 
			fab_ar[i].fir_top = std::stoi(in_string);
			file >> bufor;
			string_index = 0;
			in_char = bufor[string_index];
			in_string.clear();
			in_string.resize(3);
			amount_digit = 0;

			while (in_char != 'x') { //wczytanie szerokoœci
				in_string[string_index] = bufor[string_index];
				in_char = bufor[++string_index];
				amount_digit++;
			}
			fab_ar[i].width = std::stoi(in_string);
			in_char = bufor[++string_index];
			in_string.clear();
			in_string.resize(3);

			while (in_char >= '0' && in_char<='9') { //wczytywanie wysokoœci
				in_string[string_index-amount_digit -1] = bufor[string_index];
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

	char fab_ar2[array_size][array_size];

	for (int i = 0; i < array_size; i++) {
		for (int j = 0; j < array_size; j++) {
			fab_ar2[i][j] = '.';
		}
	}
	int number_of_x1 = 0;
	for (int i = 0; i < parts_amount; i++) { //po wszystkich 1305 kawa³kach

		for (int a = fab_ar[i].fir_left; a < fab_ar[i].width + fab_ar[i].fir_left; a++) {
			for (int b = fab_ar[i].fir_top; b < fab_ar[i].height + fab_ar[i].fir_top; b++) {
				if (fab_ar2[a][b] == 'A') {
					fab_ar2[a][b] = 'x';
					number_of_x1++;
				}
				else if (fab_ar2[a][b] == '.')
					fab_ar2[a][b] = 'A';
			}
		}
	}

	std::cout << number_of_x1;
}