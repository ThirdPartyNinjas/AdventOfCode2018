#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

namespace Advent
{
	std::vector<char> LoadUnits()
	{
		std::vector<char> units;

		std::fstream input{ "day5_input.txt" };
		for (char c; input >> c;)
		{
			units.push_back(c);
		}

		return units;
	}

	void ProcessReactions(std::vector<char> &units)
	{
		// scan left to right, removing pairs
		// repeat until a full scan fails to find any pairs

		bool found;
		do
		{
			found = false;
			size_t i = 0;
			do
			{
				if (units[i] != units[i + 1] && std::toupper(units[i]) == std::toupper(units[i + 1]))
				{
					found = true;
					units.erase(units.begin() + i, units.begin() + i + 2);
				}
				else
				{
					i++;
				}

			} while (i < units.size() - 1);
		} while (found);
	}

	void Day5A()
	{
		auto units = LoadUnits();
		ProcessReactions(units);

		std::cout << "Day 5a: The units remaing after reaction is: " << units.size() << std::endl;
	}

	void Day5B()
	{
		auto units = LoadUnits();
		size_t shortest = units.size();

		for (int i = 0; i < 26; i++)
		{
			// duplicate our units
			// remove a unit type
			// process the reaction

			auto copy = units;
			copy.erase(std::remove_if(copy.begin(), copy.end(), [i](auto c) {return c == (i + 'a') || c == (i + 'A'); }), copy.end());
			ProcessReactions(copy);

			if (copy.size() < shortest)
			{
				shortest = copy.size();
			}
		}

		std::cout << "Day 5b: The shortest polymer produced is: " << shortest << std::endl;
	}
}
