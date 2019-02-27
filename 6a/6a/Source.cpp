#include<iostream>
#include<fstream>
#include<string>
#include<vector>

constexpr int size = 400;

bool in_array(int tab[], int element) {

	for (int i = 0; i < 100; i++)
		if (tab[i] == element)
			return true;

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////

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

	for (int i = 0; i < index_letter; i++) {

		matrix[data[i][0]][data[i][1]] = value;	
		value++;
	}


	int minimal_dist = 1000, x_dist = 0, y_dist = 0, write_value = 0;
	value = 1;
	bool repetition = false;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) { 

			if (matrix[i][j] == 0) {
					for (int a = 0; a < size; a++) {
						for (int b = 0; b < size; b++) { 

							if (matrix[a][b] > 0) { //find letter
								x_dist = abs(i - a);
								y_dist = abs(j - b);

								if ((x_dist + y_dist) < minimal_dist) {
									minimal_dist = x_dist + y_dist;   //new minimal distance
									write_value = -matrix[a][b];
									repetition = false;
								}
								else if ((x_dist + y_dist) == minimal_dist) repetition = true;
							}
							else continue;
							
						}
					}
				
				if (repetition) {
					matrix[i][j] = 0;
				}
				else {
					matrix[i][j] = write_value;
					write_value = 0;
				}
				repetition = false;
				minimal_dist = 1000;
			}
		}
	}

	int edge_numbers[100]{ 0 };
	int index = 0;

	for (int i = 0; i < size; i++) {
		if (!in_array(edge_numbers, matrix[0][i])){
		edge_numbers[index] = matrix[0][i];
		index++;
	}
		}


	for (int i = 0; i < size; i++) {
		if (!in_array(edge_numbers, matrix[size - 1][i])) {
			edge_numbers[index] = matrix[size - 1][i];
			index++;
		}
	}

	for (int i = 0; i < size; i++) {
		if (!in_array(edge_numbers, matrix[i][0])) {
			edge_numbers[index] = matrix[i][0];
			index++;
		}
	}

	for (int i = 0; i < size; i++) {
		if (!in_array(edge_numbers, matrix[i][size - 1])) {
			edge_numbers[index] = matrix[i][size - 1];
			index++;
		}
	}		// find number (letter) with infinitive number of appearing

	

	int clos_field_num = 0;
	int temp_num = 0;
	int most_clos_value = 0;
	int actual_number = -1;
	value = -1;

	for (int i = 0; i < index_letter; i++) {
		for (int a = 0; a < size; a++) {
			for (int b = 0; b < size; b++) {
				if (matrix[a][b] == value) {
					temp_num++;
				}
			}
		}

		if (temp_num > clos_field_num && !in_array(edge_numbers, actual_number)) {
			clos_field_num = temp_num;
			most_clos_value = value;
		}
		temp_num = 0;
		value--;
		actual_number = value;
	} //find the number of appearing letters(numbers) without infinity


	std::cout << "\nMaximal number of closest elements: " << clos_field_num +1;
	std::cout << "\nAnd the number is " << most_clos_value;
}