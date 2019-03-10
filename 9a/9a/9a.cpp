#include<iostream>
#include<vector>

constexpr int num_of_players = 404;
constexpr int last_marble_value = 71852;

int main() {

	std::vector<int> marbles;
	std::vector<long long unsigned int> players( num_of_players, 0 );

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

	long long unsigned int highest_score = 0;

	for (int i = 0; i < num_of_players; i++) {
		if (players[i] > highest_score) {
			highest_score = players[i];
		}
	}

	std::cout << highest_score;
	}

//56 minut wykonywania xD
