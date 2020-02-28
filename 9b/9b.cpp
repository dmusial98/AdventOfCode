#include<iostream>
#include<vector>

constexpr int num_of_players = 404;
constexpr int last_marble_value = 7185200;

class Result
{
	std::vector<unsigned int> data{ 0 };
	const unsigned int max = 0 - 1;  //oveflow of unsigned int

public:
	Result operator+=(int number)
	{
		unsigned int difference = max - data[data.size() - 1];

		if (number < difference)
		{
			data[data.size() - 1] += number;
		}
		else if (number > difference)
		{
			data[data.size() - 1] += difference; //load max value into last int 
			data.push_back(number - difference); //adding new int for storing result
		}
		else //number == difference
		{
			data[data.size() - 1] += difference;
			data.push_back(0);   //adding new int for storing result
		}

		return *this;
	}

	bool operator>(Result second)
	{
		if (this->data.size() > second.data.size())
			return true;
		else if (this->data.size() < second.data.size())
			return false;
		else //this->size() == second.data.size()
		{
			if (this->data[data.size() - 1] > second.data[second.data.size() - 1])
				return true;
			else if (this->data[data.size() - 1] < second.data[second.data.size() - 1])
				return false;
			else
				return false;
		}
	}

	std::string get_number()
	{
		std::string res_str = "full integers: ";
		char full_int[24];
		
		res_str += _itoa((int)data.size() - 1, full_int, 10);

		res_str += " last int equals: ";

		res_str += _itoa(data[data.size() - 1], full_int, 10);

		return res_str;
	}
};

int main() {

	std::vector<unsigned long long int> marbles;
	std::vector<unsigned long long int> players( num_of_players, 0);

	marbles.push_back(0);
	marbles.push_back(2);
	marbles.push_back(1);
	marbles.push_back(3);

	int pos_act_marble = 3;
	int act_player = 4;

	for (int i = 4; i <= last_marble_value; i++) {

		if (i % 23 == 0) {
			if (pos_act_marble < 7) {
				pos_act_marble = marbles.size() - (7 - pos_act_marble);
				players[act_player - 1] += (marbles[pos_act_marble] + i);
				marbles.erase(marbles.begin() + pos_act_marble - 1);
			}
			else
			{
				pos_act_marble -= 7;
				players[act_player - 1] += (marbles[pos_act_marble] + i);
				marbles.erase(marbles.begin() + pos_act_marble);
			}
		}

		else if (pos_act_marble == marbles.size() - 2) {			
			marbles.push_back(i);
			pos_act_marble = marbles.size() - 1;
		}
		else if (pos_act_marble == marbles.size() - 1) {
			marbles.insert(marbles.begin() + 1, i);
			pos_act_marble = 1;
		}
		else {
			pos_act_marble += 2;
			marbles.insert(marbles.begin() + pos_act_marble, i);
		}

		if(act_player == num_of_players)
		act_player = 1;
		else act_player++;
	}

	//Result *highest_score = new Result();
	unsigned long long int highest_score = 0;


	for (int i = 0; i < num_of_players; i++) {
		if (players[i] > highest_score) {
			highest_score = players[i];
		}
	}

	std::cout << highest_score;
}
