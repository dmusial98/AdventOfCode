#include<iostream>
#include <fstream>
#include <string>
using namespace std;

constexpr int letters_size = 'z' - 'a' + 1;

int main() {

	int letters_array[letters_size] = {};
	fstream file;
	file.open("plik.txt", ios::in);
	string bufor;
	int buf_len;
	bool were_two = false;
	bool were_three = false;
	int two = 0;
	int three = 0;
	int line = 0;
	

	while(!file.eof()) {
		file >> bufor;
		buf_len = bufor.length();

		for (int i = 0; i < buf_len; i++) {
			(letters_array[bufor[i] - 'a'])++;
		}

		for (int i = 0; i < letters_size; i++) {
			if (letters_array[i] == 2 && were_two == false) {
				two++; were_two = true;
			}
			else if (letters_array[i] == 3 && were_three == false) {
				three++; were_three = true;
			}
		}

		for (int i = 0; i < letters_size; i++) {
			letters_array[i] = 0;
		}
		
		were_two = false;
		were_three = false;
	}

	cout << two * three << endl;


}