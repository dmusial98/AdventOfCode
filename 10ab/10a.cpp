#include <fstream>
#include <string>
#include <vector>

constexpr int max_array_size = 600;
constexpr int time_elapsed = 10639;

class Light
{
public:

	int x_position;
	int y_position;
	int x_velocity;
	int y_velocity;

	Light(int xp, int yp, int xv, int yv) :  x_position(xp), y_position(yp), x_velocity(xv), y_velocity(yv) {}

	void one_second_later()
	{
		x_position += x_velocity;
		y_position += y_velocity;
	}
};

void read_from_file(std::fstream &input_file, std::vector<Light> &lights)
{
	std::string buffer;
	
	std::string temp_number;
	int x_pos, y_pos, x_vel, y_vel;

	do {
		input_file >> buffer;

		if (buffer.length() == 10) //first coordinate is positive number
		{
			input_file >> buffer;

			int index = 0;

			do 
			{
				temp_number.push_back(buffer[index]);
				index++;
			} while (buffer[index] >= *"0" && buffer[index] <= *"9");  //getting first coordinate from file

			const char *temp_number_char = temp_number.c_str();

			x_pos = atoi(temp_number_char); 
		}
		else //second coordinate is negative number
		{
			int index = 10;

			do
			{
				temp_number.push_back(buffer[index]);
				index++;
			} while (buffer[index] >= *"0" && buffer[index] <= *"9");  //getting first coordinate from file

			const char *temp_number_char = temp_number.c_str();

			x_pos = atoi(temp_number_char);
		}

		temp_number.clear();

		input_file >> buffer;

		int index = 0;

		do
		{
			temp_number.push_back(buffer[index]);
		} while (buffer[++index] >= *"0" && buffer[index] <= *"9");  //getting first coordinate from file

		const char *temp_number_char = temp_number.c_str();

		y_pos = atoi(temp_number_char);

		temp_number.clear();

		input_file >> buffer;


		if (buffer.length() == 10) //third coordinate is positive number
		{
			input_file >> buffer;

			int index = 0;

			do
			{
				temp_number.push_back(buffer[index]);
			} while (buffer[++index] >= *"0" && buffer[index] <= *"9");  //getting first coordinate from file

			const char *temp_number_char = temp_number.c_str();

			x_vel = atoi(temp_number_char);
		}
		else //third coordinate is negative number
		{
			int index = 10;

			do
			{
				temp_number.push_back(buffer[index]);
			} while (buffer[++index] >= *"0" && buffer[index] <= *"9");  //getting third coordinate from file

			const char *temp_number_char = temp_number.c_str();

			x_vel = atoi(temp_number_char);
		}

		temp_number.clear();

		input_file >> buffer;

		index = 0;

		do
		{
			temp_number.push_back(buffer[index]);
		} while (buffer[++index] >= *"0" && buffer[index] <= *"9");  //getting third coordinate from file

		const char *temp_number_char1 = temp_number.c_str();

		y_vel = atoi(temp_number_char1);

		temp_number.clear();

		lights.push_back(Light(x_pos, y_pos, x_vel, y_vel));

	} while (!input_file.eof());

	input_file.close();
}

void find_max_and_min(int &max_x, int &min_x, int &max_y, int &min_y, std::vector<Light> &lights)
{
	for (int i = 0; i < lights.size(); i++)
	{
		if (lights[i].x_position > max_x)
			max_x = lights[i].x_position;
		if (lights[i].x_position < min_x)
			min_x = lights[i].x_position;
		if (lights[i].y_position > max_y)
			max_y = lights[i].y_position;
		if (lights[i].y_position < min_y)
			min_y = lights[i].y_position;
	}
}

void clean_sky_array(char **sky_array)
{
	for (int i = 0; i < max_array_size; i++)
	{
		for (int j = 0; j < max_array_size; j++)
			sky_array[i][j] = *".";
	}
}

void save_to_file(std::string name_of_file, char** sky_array)
{
	std::fstream output_file;
	output_file.open(name_of_file, std::ios_base::out);


	for (int i = 0; i < max_array_size; i++)
	{
		for (int j = 0; j < max_array_size; j++)
		{
			output_file << sky_array[j][i];
		}

		output_file << "\n";
	}

	output_file.close();
}

int main()
{
	std::vector<Light> lights;

	std::fstream input_file;
	input_file.open("input.txt");

	read_from_file(input_file, lights);

	for (int i = 0; i < time_elapsed; i++)
	{
		for (int j = 0; j < lights.size(); j++)
		{
			lights[j].one_second_later();
		}
	}

	char* sky_array[max_array_size];

	for (int i = 0; i < max_array_size; i++)
		sky_array[i] = new char[max_array_size]; //creating array for lights
	
	clean_sky_array(sky_array);

	for (int j = 0; j < lights.size(); j++)
	{
		sky_array[max_array_size/2 + lights[j].x_position][max_array_size/2 + lights[j].y_position] = *"#";
	}
		
	std::string name_of_file = "output_file.txt";
	save_to_file(name_of_file, sky_array);

}