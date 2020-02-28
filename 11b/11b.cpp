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
	int max_value_grid = -1000000;
	int square_size = 0;

	for (int i = 0; i < 300; i++)
	{
		for (int j = 0; j < 300; j++)
		{			
			for (int s = 0; s < 300; s++) //size of square
			{
				int temp_value_grid = 0;

				if (i + s < 300 && j + s < 300)
				{
					for (int k = 0; k < s; k++)
					{
						for (int m = 0; m < s; m++)
						{
							temp_value_grid += fuel_cell_grid[i + k][j + m];
						}
					}

					if (temp_value_grid > max_value_grid)
					{
						max_value_grid = temp_value_grid;
						index_x_max = i + 1;
						index_y_max = j + 1;
						square_size = s;
					}
				}
			}
			

		}
	} //finding index of maximal value 3x3 square in all grid

	std::cout << index_x_max << "," << index_y_max << "," << square_size;
}