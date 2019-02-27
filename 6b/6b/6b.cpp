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
	}  //load from file

	value = -1;
	int matrix[size][size]{ 0 };

	for (int i = 0; i < index_letter; i++) {

		matrix[data[i][0]][data[i][1]] = value;
		value--;
	}  //filling matrix


	int summarise_dist = 0, x_dist = 0, y_dist = 0, index = 0;
	int sum_dist_letters_array[100]{ 0 };

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			for (int a = 0; a < size; a++) {
				for (int b = 0; b < size; b++) {
					if (matrix[a][b] < 0) { //find letter
						x_dist = abs(i - a);
						y_dist = abs(j - b);
						summarise_dist += (x_dist + y_dist);
					}
				}
			}

			if (matrix[i][j] == 0) {
					matrix[i][j] = summarise_dist;
				} 
					else if(matrix[i][j] < 0) {
						sum_dist_letters_array[index] = summarise_dist;
						index++;
						}

			summarise_dist = 0;
		}
	}

	int number_of_elem = 0;
	
		for (int a = 0; a < size; a++) {
			for (int b = 0; b < size; b++) {
				if (matrix[a][b] < 10000 && matrix[a][b] > 0) {
					number_of_elem++;
				}
			}
		}

		for (int i = 0; i < 100; i++) {
			if (sum_dist_letters_array[i] < 10000 && sum_dist_letters_array[i] > 0)
				number_of_elem++;
		}

	std::cout << "\nNumber of elements with summarise distance less than 10000: " << number_of_elem;
}