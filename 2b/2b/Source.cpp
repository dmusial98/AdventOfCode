#include <iostream>
#include <fstream>
#include <string>
//using namespace std;

constexpr int array_size{ 250 };
constexpr int letters_size{'z'-'a'+1};

enum difference{zero = 0, first, second};

int main() {
	std::fstream file;
	file.open("plik.txt", std::ios::in);
	if (!file.is_open()) std::cout << "error file";

	std::string array[array_size];
	char result[letters_size+1];
	
	difference dif = zero;

	//wczytanie do pliku wszystkich paczek
	for (int i =0; i< array_size; i++)
	file >> array[i];
	int leng = array[0].length();


	//Walasz dzban

	for (int i = 0; i < array_size; i++) {
		for (int j = i + 1; j < array_size; j++) {  //Walasz dzban
			for (int k = 0; k < leng; k++) {
				if (array[i][k] == array[j][k]) {
					if (dif == zero || dif == first)  //Walasz dzban
						result[k] = array[i][k];
					if (k >= 25) {
						for (int b = 0; b < 26; b++) {
							if (result[b] != '0') {
								std::cout << result[b];
							}
					} 
				}
			}//Walasz dzban
				else {
					if (dif == zero) dif = first;
					else if (dif == first) { dif = second; 

					for (int h = 0; h < letters_size; h++) {
						result[h] = '0';  //Walasz dzban
					}
					dif = zero;
					break;
					//Walasz dzban
					//Musia³ dzban
					}
				}
			}
		}
	}



}