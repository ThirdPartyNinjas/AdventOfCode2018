#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Advent
{
	void Day3A()
	{
		std::fstream input{ "day3_input.txt" };

		std::string s;
		char c;
		int x, y, width, height;

		std::vector<std::vector<int>> grid(1000, std::vector<int>(1000));

		while (input >> s >> s >> x >> c >> y >> s >> width >> c >> height)
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					grid[y + i][x + j]++;
				}
			}
		}

		int count = 0;

		for (int i = 0; i < 1000; i++)
		{
			for (int j = 0; j < 1000; j++)
			{
				if (grid[i][j] >= 2)
				{
					count++;
				}
			}
		}

		std::cout << "Day 3a: The number of square inches in two or more claims: " << count << std::endl;
	}

	void Day3B()
	{
		// gonna be lazy and reuse the code above, which means reading everything in twice

		std::vector<std::vector<int>> grid(1000, std::vector<int>(1000));
		int result = -1;

		{
			std::fstream input{ "day3_input.txt" };

			std::string s;
			char c;
			int x, y, width, height;

			while (input >> s >> s >> x >> c >> y >> s >> width >> c >> height)
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						grid[y + i][x + j]++;
					}
				}
			}
		}

		{
			std::fstream input{ "day3_input.txt" };

			std::string s;
			char c;
			int claim, x, y, width, height;

			while (input >> c >> claim >> s >> x >> c >> y >> s >> width >> c >> height)
			{
				bool failed = false;

				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						if (grid[y + i][x + j] != 1)
						{
							failed = true;
							break;
						}
					}
					if (failed)
						break;
				}

				if (!failed)
				{
					result = claim;
				}
			}
		}
		std::cout << "Day 3b: The claim that doesn't overlap is: " << result << std::endl;
	}
}
