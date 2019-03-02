#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

#define NUM_OF_LET 26

bool in_vector(std::vector<char> vec, char let) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == let) return true;
	}

	return false;
}

int main() {

	std::fstream file;
	file.open("file.txt", std::ios::ios_base::in);
	if (!file.is_open()) std::cout << "file error";
	char buffer[100]{ 0 };
	std::string buf;
		
	std::vector<std::vector<char>> data;
	int index_letter = 0;
	   
	while (!file.eof()) {
		file.getline(buffer, 50);
		buf = buffer;

		data.push_back(std::vector<char>());  //add new row

		for (int i = 1; i < buf.length(); i++) {  // i != 0, because first letter is unnecessary
			if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
				data[index_letter].push_back(buffer[i]); //both characters in vector
			}
		}

		index_letter++;
	}  //load from file
	file.close();

	std::vector<char> final_sequence;
	std::vector<char> temp_let;
	std::vector<std::vector<char>> needed_let;

	for (int i = 0; i < NUM_OF_LET; i++) {
		needed_let.push_back(std::vector<char>());
	}

	
	for (char i = 'A'; i <= 'Z'; i++) {
		for (int j = 0; j < index_letter; j++) {
			if (data[j][1] == i) {		//find possible letter for adding to a queue
				needed_let[i - 'A'].push_back(data[j][0]);
			}
		}
	}

	for (int i = 0; i < NUM_OF_LET; i++) {
		if (needed_let[i].size() == 0) {
			temp_let.push_back(i + 'A');
		}
	} //first part of letters in temp_let

	final_sequence.push_back(temp_let[0]);
	temp_let.erase(temp_let.begin());

	bool possible_letter{ true };

	while (final_sequence.size() != NUM_OF_LET) {

		for (int i = 0; i < NUM_OF_LET; i++) {
			for (int j = 0; j < needed_let[i].size(); j++) {
				if (!in_vector(final_sequence, needed_let[i][j])) {
				possible_letter = false;
				break;
			}
			}
			if(possible_letter)
			temp_let.push_back(i + 'A');

			possible_letter = true;
		}
		
		
		//giving new letters to a queue for writing to final_sequence
		
		
		std::sort(temp_let.begin(), temp_let.end());
		
		for (int i = 0; i < temp_let.size(); i++) {
			for (int j = i + 1; j < temp_let.size(); j++) {
				if (temp_let[j] == temp_let[i]) {
					temp_let.erase(temp_let.begin() + j);
				}
			}
		} //erase all repetitions

		for (int i = 0; i < final_sequence.size() ; i++) {
			for (int j = 0; j < temp_let.size(); j++) {
				if (temp_let[j] == final_sequence[i]) {
					temp_let.erase(temp_let.begin() + j);
				}
			}
		}  //erase all repetitions with letters which were written

		final_sequence.push_back(temp_let[0]);
		temp_let.erase(temp_let.begin());

	}


	for (int i = 0; i < NUM_OF_LET; i++) {
		std::cout << final_sequence[i];
	}

}