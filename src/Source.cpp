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
	if (path.empty())
		return false;

	// Check if it is a cycle.
	if (matrix[path.back()][path[0]] == 1)
		// It is a cycle! Now check if ball room was reached on path. If not, path is unnedded.
		for (const auto& e : path)
			if (e == ballRoom - 1)
				return true;

	return false;
}

Matrix RemoveTop(Matrix matrix, int top)
{
	std::fill(matrix[top].begin(), matrix[top].end(), 0);
	std::for_each(matrix.begin(), matrix.end(), [top](auto& v) {v[top] = 0; });

	return std::move(matrix);
}

std::vector<int> findPath(Matrix matrix, int ballRoom, int firstTop)
{
	std::vector <int> path(MaxSize(matrix));
	std::vector <bool> visited(matrix.size(), false);

	if (DFS(matrix, firstTop, path, visited, 0) && checkRequirements(path, ballRoom, matrix))
		return path;
	else
	{
		for (int i = 1; i <= MaxSize(matrix); ++i)
		{
			for (int j = 0; j < MaxSize(matrix); ++j)
			{
				std::vector <int> shorterPath(MaxSize(matrix) - i);
				std::fill(visited.begin(), visited.end(), false);

				if (j != firstTop && DFS(RemoveTop(matrix, j), firstTop, shorterPath, visited, 0) && checkRequirements(shorterPath, ballRoom, matrix))
					return shorterPath;
			}
		}
	}
	return {};
}

Matrix findPaths(Matrix matrix, int ballRoom)
{
	// Setup some algorithm variables
	Matrix paths;

	// If there are any nodes with degree more than 1
	if (MaxSize(matrix) != 0)
	{
		// Look for possible paths
		for (int firstTop = 0; firstTop < matrix.size(); ++firstTop)
		{
			const auto found = findPath(matrix, ballRoom, firstTop);
			if (!found.empty())
			{
				paths.push_back(found);
			}
		}
	}

	return paths;
}

bool validateGraph(Matrix matrix)
{
	for (size_t i{}; i < matrix.size(); ++i)
	{
		if (matrix.at(i).at(i) == 1)
			return false;
	}
	return true;
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

	if (!validateGraph(matrix))
	{
		std::cout << "Graph is incorrect.\n";
	}
	else
	{
		const auto paths = findPaths(matrix, ballRoom);

		// Write paths down on the console
		if (paths.empty())
		{
			std::cout << "There is no proper path.\n";
		}
		else
		{
			std::cout << "Existing paths:\n";
			readMatrix(paths, " -> ", true);
		}
	}

	// Prevent from closing the console automatically
	system("pause");
	return 0;
}