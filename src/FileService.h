#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


using Matrix = std::vector<std::vector <int>>;

bool readFile(int& ballRoom, Matrix& matrix)
{
	ballRoom = -1;
	matrix.clear();

	const auto string2vec = [](std::string& line)
	{
		std::vector<int> tmp;
		for (size_t i = 0; (i * 2) < line.size(); ++i)
			tmp.emplace_back(line[i * 2] - '0');

		return std::move(tmp);
	};

	std::fstream file;
	file.open("InputData.txt", std::ios::in);

	if (file.bad() || file.fail())
		return false;

	std::string line;

	while (getline(file, line))
	{
		if (line[0] == '#' || line.empty())
			continue;

		if (ballRoom == -1)
		{
			ballRoom = line[0] - '0';
		}
		else
		{
			matrix.emplace_back(string2vec(line));
		}
	}

	file.close();
	return true;
}
