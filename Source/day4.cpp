#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace Advent
{
	enum class Event
	{
		Shift,
		Sleep,
		Wake
	};

	struct Entry
	{
		int year, month, day, hour, minute, id;
		Event event;
	};

	std::map<int, std::vector<int>> GetGuardMinutes()
	{
		std::fstream input{ "day4_input.txt" };

		char c;
		std::string s;
		Entry entry;
		std::vector<Entry> entries;

		while (input >> c >> entry.year >> c >> entry.month >> c >> entry.day >> entry.hour >> c >> entry.minute >> c >> s)
		{
			if (s == "Guard")
			{
				input >> c >> entry.id;
				entry.event = Event::Shift;
			}
			else if (s == "falls")
			{
				entry.id = -1;
				entry.event = Event::Sleep;
			}
			else if (s == "wakes")
			{
				entry.id = -1;
				entry.event = Event::Wake;
			}

			entries.push_back(entry);

			std::getline(input, s);
		}

		std::sort(entries.begin(), entries.end(), [](const auto &a, const auto &b)
		{
			if (a.year != b.year)
				return a.year < b.year;
			if (a.month != b.month)
				return a.month < b.month;
			if (a.day != b.day)
				return a.day < b.day;
			if (a.hour != b.hour)
				return a.hour < b.hour;
			return a.minute < b.minute;
		});

		int currentId = -1;
		int startMinute;

		std::map<int, std::vector<int>> guards;

		for (auto &e : entries)
		{
			switch (e.event)
			{
				case Event::Shift:
					currentId = e.id;
					if (guards.find(e.id) == guards.end())
						guards[e.id] = std::vector<int>(60);
					break;

				case Event::Sleep:
					startMinute = (e.hour == 23) ? 0 : e.minute;
					break;

				case Event::Wake:
					for (int i = startMinute; i < e.minute; i++)
					{
						guards[currentId][i]++;
					}
					break;
			}
		}

		return guards;
	}

	void Day4A()
	{
		auto guards = GetGuardMinutes();

		int sleepyGuard = -1;
		int maxMinutes = -1;

		for (auto &g : guards)
		{
			int total = 0;
			for (int i = 0; i < 60; i++)
			{
				total += g.second[i];
			}

			if (total > maxMinutes)
			{
				maxMinutes = total;
				sleepyGuard = g.first;
			}
		}

		int sleepyMinute = -1;
		maxMinutes = -1;

		for (int i = 0; i < 60; i++)
		{
			if (guards[sleepyGuard][i] > maxMinutes)
			{
				maxMinutes = guards[sleepyGuard][i];
				sleepyMinute = i;
			}
		}

		std::cout << "Day 4a: The sleepy guard number is: " << sleepyGuard * sleepyMinute << std::endl;
	}

	void Day4B()
	{
		auto guards = GetGuardMinutes();

		int sleepyGuard = -1;
		int sleepyMinute = -1;
		int maxMinute = -1;

		for (auto &g : guards)
		{
			for (int i = 0; i < 60; i++)
			{
				if (g.second[i] > maxMinute)
				{
					maxMinute = g.second[i];
					sleepyMinute = i;
					sleepyGuard = g.first;
				}
			}
		}

		std::cout << "Day 4b: The sleepy guard number is: " << sleepyGuard * sleepyMinute << std::endl;
	}
}
