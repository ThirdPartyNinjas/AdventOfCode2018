#include <fstream>
#include <iostream>
#include <set>
#include <vector>

namespace Advent
{
	void Day1A()
	{
		std::fstream input{ "day1_input.txt" };

		int sum = 0;
		for(int current; input >> current;)
		{
			sum += current;
		}

		std::cout << "Day 1a: The frequency is: " << sum << std::endl;
	}

	void Day1B()
	{
		std::fstream input{ "day1_input.txt" };

		std::vector<int> list;
		for (int current; input >> current;)
		{
			list.push_back(current);
		}

		std::set<int> set;
		int sum = 0;
		bool finished = false;
		while (!finished)
		{
			for (auto temp : list)
			{
				// do the test first, so we'll be sure to add the starting value of zero
				if (set.count(sum))
				{
					finished = true;
					break;
				}
				
				set.insert(sum);
				sum += temp;
			}
		}

		std::cout << "Day 1b: The first frequency encountered twice is: " << sum << std::endl;
	}
}
