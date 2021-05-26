#include "FileService.h"

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>

bool DFS(const Matrix& matrix, int currentNode, std::vector <int>& path, std::vector <bool>& visited, int iteration)
{
	// If iteration is out of the path size, stop looking for next node
	if (iteration >= path.size())
		return true;

	// Set actual node in the path and mark as visited
	path[iteration] = currentNode;
	visited[currentNode] = true;

	// Check all possible next nodes if any has connection and if it hasn't been visited yet
	for (int nextTop = 0; nextTop < matrix.size(); ++nextTop)
	{
		if (matrix[currentNode][nextTop] == 1 && (!visited[nextTop] || (iteration + 1 == path.size() && nextTop == path[0])))
		{
			if (DFS(matrix, nextTop, path, visited, iteration + 1))
				return true;
		}
	}

	// If all have been visited then it is needed to go back by one node
	visited[currentNode] = false;

	return false;
}

/// Amount of nodes with degree more than 1
size_t MaxSize(const Matrix& matrix)
{
	// Variable for calculations
	size_t max = 0;

	// Incremetation of the max variable every time sum of elements in row is bigger than 1
	for (int i = 0; i < matrix.size(); ++i)
		if (1 < std::accumulate(matrix[i].begin(), matrix[i].end(), 0))
			++max;

	return max;
}

/// Writes matrix into the console
void readMatrix(const Matrix& matrix, const char* colDelimiter = " ", bool isPath = false)
{
	for (const auto& e : matrix)
	{
		for (const auto& e2 : e)
			std::cout << e2 + isPath << colDelimiter;
		if (isPath)
			std::cout << e.front() + isPath;
		std::cout << std::endl;
	}
}

/// Check task requirements and return only correct paths
bool checkRequirements(const std::vector<int>& path, const int ballRoom, const Matrix& matrix)
{
	// Check if it is a cycle.
	if (matrix[path.back()][path[0]] == 1)
		// It is a cycle! Now check if ball room was reached on path. If not, path is unnedded.
		for (const auto& e : path)
			if (e == ballRoom - 1)
				return true;

	return false;
}

Matrix RemoveTop(Matrix& matrix, int top)
{
	Matrix tmp = matrix;
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)
		{
			if (i == top || j == top)
			{
				tmp[i][j] = 0;
			}
		}
	}
	return tmp;
}

int main()
{
	// Most important variables
	Matrix matrix;
	int ballRoom = -1;

	// File reading
	if (!readFile(ballRoom, matrix))
	{
		std::cout << "Bad file" << std::endl;
		return -1;
	}

	// Writting variables into console
	std::cout << "Graph taken into consideration:\n";
	readMatrix(matrix);
	std::cout << "\nwhere ball room is in " << ballRoom << " node.\n\n";

	// Setup some algorithm variables
	Matrix paths;
	std::vector <bool> visited(matrix.size());
	std::vector <int> path(MaxSize(matrix));

	// If there are any nodes with degree more than 1
	if (path.size() != 0)
	{
		// Look for possible paths
		for (int firstTop = 0; firstTop < matrix.size(); ++firstTop)
		{
			std::fill(visited.begin(), visited.end(), false);
			if (DFS(matrix, firstTop, path, visited, 0) && checkRequirements(path, ballRoom, matrix))
				paths.push_back(path);
		}
	}

	// Write paths down on the console
	if (paths.empty())
	{
		std::cout << "There is no proper path.\n";
	}
	else
	{
		std::cout << "Existing paths:\n";
		readMatrix(paths, " -> ", true);
		if (!IF_FIND)
		{
			std::cout << "not find" << std::endl;
			for (int i = 1; i <= MaxSize(matrix); ++i)
			{
				for (int j = 0; j < MaxSize(matrix); ++j)
				{
					if (j != FirstTop)
						DFS(RemoveTop(matrix, j), FirstTop, SecondTop, stack, visited, MaxSize(matrix) - i, ballRoom, 0);
					if (IF_FIND)
						break;
				}
				if (IF_FIND)
					break;
			}
		}
		IF_FIND = false;
	}

	// Prevent from closing the console automatically
	system("pause");
	return 0;
}