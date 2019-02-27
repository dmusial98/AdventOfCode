#include<iostream>
#include<fstream>
#include<string>
#include<vector>

constexpr int size = 400;

int main() {

	std::fstream file;
	file.open("file.txt", std::ios::ios_base::in);


	std::vector<std::vector<int>> data;
	std::string buf; //comma disturb for int loading from file

	int index_letter{ 0 };
	int value;
	
	while (file >> buf) {

		value = stoi(buf);

		data.push_back(std::vector<int>());  //new row of integers	
		data[index_letter].push_back(value); //new value in row
		file >> buf; //second value of cords
		value = stoi(buf);

		data[index_letter].push_back(value);

		index_letter++;
	}

	value = 1;
	int matrix[size][size]{ 0 };

	for (int i = 0; i < index_letter - 1; i++) {

		matrix[data[i][0]][data[i][1]] = value;	
		value++;
	}


	int minimal_dist = 1000, x_dist = 0, y_dist = 0, write_value = 0;
	value = 1;
	bool repetition = false;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) { 


			if (matrix[i-1][j-1] == 0) {

				for (int h = 0; h < index_letter - 1; h++) { //find all letters
					
					for (int a = 0; a < size; a++) {
						for (int b = 0; b < size; b++) { 
							if (matrix[a][b] == value) { //find value of letter
								x_dist = abs(i - a);
								y_dist = abs(j - b);

								if ((x_dist + y_dist) < minimal_dist) {
									minimal_dist = x_dist + y_dist;   //new minimal distance
									write_value = -value;
									repetition = false;
								}
								else if ((x_dist + y_dist) == minimal_dist) repetition = true;
							
								value++;
							}
							else continue;
						}
					}
				}
				if (repetition) {
					matrix[i][j] = 0;
				}
				else {
					matrix[i][j] = write_value;
					write_value = 0;
					value = 1;
				}
				repetition = false;
			}
		}
	}

	

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}



}