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
	inp_vec.resize(strings[0].size() +strings[1].size() + strings[2].size() +strings[3].size() +strings[4].size());

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


	bool was_explosion = true;

	while (was_explosion) {
		was_explosion = false;
		for (unsigned int i = 0; i < inp_vec.size() - 1; i++) {

			if (abs(inp_vec[i] - inp_vec[i + 1]) == 32) {
				inp_vec.erase(inp_vec.begin() + i, inp_vec.begin() + i + 2);
				//inp_vec.erase(inp_vec.begin() + i);
				was_explosion = true;
			}
		}
	}

	std::cout << inp_vec.size();
}