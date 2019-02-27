#include <iostream>
#include <fstream>
#include<string>


using namespace std;

void read_from_file(int array[])
{
	fstream plik;
	plik.open("plik.txt", ios::in);
	if (plik.is_open() == false) cout << "Problems with file/n/n";
	int i = 0;
	string str_bufor;


	while (!plik.eof()) {
		plik >> str_bufor;

		array[i] = stoi(str_bufor);

		i++;
	}
	array[i] = 0;
} 

int main() {
	fstream plik;
	int array1[150000];
	int array2[990];
	read_from_file(array2);

	
	int total = 0;
	int line_number = 0;
	int index = 0;
	bool powt = false;

	while (powt == false) {
		
		while (array2[line_number] != 0)
		{
			
			total += array2[line_number];
			array1[index] = total;

			for (int i = index - 1; i >= 0; i--) {
				if (array1[index] == array1[i]) {
					powt = true;
					cout << array1[i] << "   " << array1[index] << endl;
				}
			}

			line_number++;
			index++;
		}
		line_number = 0;
		plik.seekg(0, plik.beg);
	}

}

//37,5 sekundy :D