#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace Advent
{
	void Day2A()
	{
		std::fstream input{ "day2_input.txt" };

		int sum = 0;
		std::string line;
		int twos = 0;
		int threes = 0;

		for (std::string line; input >> line;)
		{
			std::map<char, int> counts;

			for (auto c : line)
			{
				auto it = counts.find(c);
				if (it != counts.end())
					it->second++;
				else
					counts[c] = 1;
			}

			bool foundTwos = false;
			bool foundThrees = false;
			for (auto kvp : counts)
			{
				if (kvp.second == 2)
					foundTwos = true;
				else if (kvp.second == 3)
					foundThrees = true;
			}

			if (foundTwos)
				twos++;
			if (foundThrees)
				threes++;
		}

		std::cout << "Day 2a: The checksum is: " << twos * threes << std::endl;
	}

	void Day2B()
	{
		std::fstream input{ "day2_input.txt" };
		std::string output;

		std::vector<std::string> lines;
		for (std::string line; input >> line;)
		{
			lines.push_back(line);
		}

		for (size_t i = 0; i < lines.size() - 1; i++)
		{
			for (size_t j = i + 1; j < lines.size(); j++)
			{
				int wrongOffset = -1;
				for (size_t k = 0; k < lines[i].length(); k++)
				{
					if (lines[i][k] != lines[j][k])
					{
						if (wrongOffset == -1)
						{
							wrongOffset = k;
						}
						else
						{
							wrongOffset = -1;
							break;
						}
					}
				}
				if (wrongOffset != -1)
				{
					output = lines[i].erase(wrongOffset, 1);
				}
			}
		}

		std::cout << "Day 2b: The common letters are: " << output << std::endl;
	}
}
