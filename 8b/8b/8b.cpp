#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Tree {
public:
	int num_of_nodes = 0;
	int num_of_values = 0;
	std::vector<Tree*> nodes;
	std::vector<int> values;

	friend int count(Tree *tree);
	friend Tree* add_node(Tree *tr, std::fstream &file);
};

Tree* add_node(Tree *tr, std::fstream &file)
{

	file >> tr->num_of_nodes;
	file >> tr->num_of_values;

	Tree *new_tr = new Tree [tr->num_of_nodes];

	for (int i = 0; i < tr->num_of_nodes; i++) {
		tr->nodes.push_back(add_node(&new_tr[i], file));
	}

	int buf;

	for (int i = 0; i < tr->num_of_values; i++) {
		file >> buf;
		tr->values.push_back(buf);
	}

	return tr;
}

int count(Tree *tree) {

	int number = 0;

	if (tree->num_of_nodes == 0) 
	{
		for (int i = 0; i < tree->num_of_values; i++) 
		{
			number += tree->values[i];
		}
	}
	else
	{
		for (int i = 0; i < tree->num_of_values; i++) 
		{
			if (tree->values[i] <= tree->num_of_nodes) //zliczanie tego co siê da
			{
				number += count(tree->nodes[tree->values[i] - 1]);
			}
			
		}
	}

	return number;

}

int main() {

	std::fstream file;
	file.open("file.txt", std::ios::ios_base::in);

	Tree* tr = new Tree;
	add_node(tr, file);

	file.close();
	std::cout << count(tr);
}




