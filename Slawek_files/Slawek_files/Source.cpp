#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int main() {
	fstream plik;
	string pierwsza, druga;
	plik.open("plik.txt", ios::in | ios::out);
	if (plik.good()) {

		getline(plik, pierwsza);
		getline(plik, druga);
		cout << "Odczytuje: " << endl << pierwsza << endl << druga << endl << endl;
		cout << "tellg: " << plik.tellg() << " tellp: " << plik.tellp() << endl;
		plik.seekg(8);
		string trzecia;
		getline(plik, trzecia);
		cout << "Ocdczyt //Dawid " << trzecia << endl;
		//plik.seekp(0);
		
		cout << "tellg: " << plik.tellg() << " tellp: " << plik.tellp() << endl;
		cout << "Zapisuje: " << endl << pierwsza << endl << "NIESPODZIANKA!!!" << endl << druga << endl << endl;
		plik << pierwsza << endl << "NIESPODZIANKA!!!" << endl << druga;
		plik.close();
	}

	else
		cout << "blad otwarcia pliku!";


	system("pause");
	return 0;
}