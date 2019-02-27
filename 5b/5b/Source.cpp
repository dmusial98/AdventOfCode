#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

int main() {

	std::fstream file;
	file.open("file.txt", std::ios::in);

	char text[5][16301];

	std::string strings[5];


	for (int i = 0; i < 5; i++) {
		file.get(text[i], 16301);
	}

	for (int i = 0; i < 5; i++) {
		strings[i] = text[i];
	}

	std::vector<char> inp_vec(sizeof(char));
	inp_vec.resize(strings[0].size() + strings[1].size() + strings[2].size() + strings[3].size() + strings[4].size());

	int a = 0;
	bool bre = false;

	for (int i = 0; i < 5; i++) { //kopiowanie stringa do wektora

		if (bre) break;

		for (int j = 0; j < 16300; j++) {

			if (i == 3 && j == 1100) { bre = true; break; }
			inp_vec[a] = strings[i][j];
			a++;
		}
	}

	std::vector<char> tem_inp_vec(sizeof(char));
	tem_inp_vec.resize(inp_vec.size());

	for (int i = 0; i < inp_vec.size(); i++) {
		tem_inp_vec[i] = inp_vec[i];

	}

	int min = strings[0].size() + strings[1].size() + strings[2].size() + strings[3].size() + strings[4].size();
	bool was_explosion = true;

	for (unsigned int i = 'a'; i <= 'z'; i++) {

		for (int j = inp_vec.size() -1; j >= 0; j--) {		//usuniêcie danej litery
			if (inp_vec[j] == i || inp_vec[j] == i - 32) {
				inp_vec.erase(inp_vec.begin() + j);
			}			
		}
		while (was_explosion) {  //zaprzestanie gdy nie bêdzie ju¿ nic ze sob¹ reagowa³o
			was_explosion = false;
			for (unsigned int k = 0; k < inp_vec.size() - 1; k++) {

				if (abs(inp_vec[k] - inp_vec[k + 1]) == 32) {
					inp_vec.erase(inp_vec.begin() + k, inp_vec.begin() + k + 2);  //usuniêcie w przedziale [first, last)
					was_explosion = true;
				}
			}
		}
		was_explosion = true;
		if (inp_vec.size() < min) min = inp_vec.size();  

		inp_vec.resize(50000);

		for (int m = 0; m < tem_inp_vec.size(); m++) {
			inp_vec[m] = tem_inp_vec[m];
		} //przywrócenie wartoœci pocz¹tkowej
			
	}

	int index_of_max;

	
	std::cout << min;
}