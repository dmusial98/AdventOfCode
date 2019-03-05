#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int summary = 0;

class Tree {
public:
	int num_of_nodes = 0;
	int num_of_values = 0;
	std::vector<Tree*> nodes;
	std::vector<int> values;

	friend Tree* add_node(Tree &tr, std::fstream &file);
};

Tree* add_node(Tree &tr, std::fstream &file)
{
	Tree *new_tr = new Tree;

	file >> tr.num_of_nodes;
	file >> tr.num_of_values;

	for (int i = 0; i < tr.num_of_nodes; i++) {
		tr.nodes.push_back(add_node(*new_tr, file));
	}

	int buf;

	for (int i = 0; i < tr.num_of_values; i++) {
		file >> buf;
		tr.values.push_back(buf);
		summary += buf;
	}

	return new_tr;
}

int main() {

	std::fstream file;
	file.open("file.txt", std::ios::ios_base::in);

	Tree* tr = new Tree;
	add_node(*tr, file);
	
	file.close();
	std::cout << summary;
}


