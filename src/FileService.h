#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


using Matrix = std::vector<std::vector <int>>;

void readFile(int& ballRoom, Matrix& matrix)
{
	ballRoom = -1;
	matrix.clear();
	int size_x = -1;
	int size_y = -1;

	const auto string2vec = [size_x](std::string& line)
	{
		std::vector<int> tmp;
		for (size_t i = 0; i < size_x; ++i)
			tmp.emplace_back(line[i * 2] - '0');

		return tmp;
	};

	std::fstream file;
	file.open("inputData.txt", std::ios::in);
	std::string line;

	while (getline(file, line))
	{
		if (line[0] == '#' || line.empty())
			continue;

		if (size_x == -1 || size_y == -1)
		{
			size_x = line[0];
			size_y = line[2];
		}
		else if (ballRoom == -1)
		{
			ballRoom = line[0];
		}
		else
		{
			for (auto i = 0; i < size_x; ++i)
				matrix.push_back(string2vec(line));
		}
	}

	file.close();
}
