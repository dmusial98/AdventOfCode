#include <iostream>

constexpr int grid_serial_number = 5093;

int main()
{
	int fuel_cell_grid[300][300];


	for (int i = 0; i < 300; i++)
	{
		for (int j = 0; j < 300; j++)
		{
			int rack_ID = i + 11;
			int value = rack_ID * (j + 1);
			value += grid_serial_number;
			value *= rack_ID;
			value %= 1000;
			value /= 100;
			value -= 5;

			fuel_cell_grid[i][j] = value;
		}
	}  //counting values for grid

	int index_x_max = 0;
	int index_y_max = 0;
	int max_value_grid = -10;

	for (int i = 1; i < 299; i++)
	{
		for (int j = 1; j < 299; j++)
		{
			int temp_value_grid = 0;

			for (int k = -1; k < 2; k++)
			{
				for (int m = -1; m < 2; m++)
				{
					temp_value_grid += fuel_cell_grid[i + k][j + m];
				}
			}

			if (temp_value_grid > max_value_grid)
			{
				max_value_grid = temp_value_grid;
				index_x_max = i;
				index_y_max = j;
			}
			
		}
	} //finding index of maximal value 3x3 square in all grid

	std::cout << index_x_max << "," << index_y_max;
}