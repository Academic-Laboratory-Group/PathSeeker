#include "FileService.h"

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>


void DFS(const Matrix& matrix, int currentNode, std::vector <int>& stack, std::vector <bool>& visited, int& ballroom, int iteration)
{
	// Push actual node into the stack
	stack[iteration++] = currentNode;

	if (iteration < stack.size())
	{
		// Mark node as visited
		visited[currentNode] = true;

		// Check all possible next nodes if any has connection and if it hasn't been visited yet
		for (int nextTop = 0; nextTop < matrix.size(); ++nextTop)
			if (matrix[currentNode][nextTop] == 1 && !visited[nextTop])
				DFS(matrix, nextTop, stack, visited, ballroom, iteration);

		// If all have been visited then it is needed to go back by one node
		visited[currentNode] = false;
		--iteration;
	}
	else
	{
		// Path is finded. Now check if it is a cycle. 
		for (int nextTop = 0; nextTop < matrix.size(); ++nextTop)
		{
			// Is this neighbour of currentNode first in the stack?
			if (matrix[currentNode][nextTop] == 1 && nextTop == stack[0])
			{
				// It is a cycle! Now check if ball room was reached on path. If not, path is unnedded.
				for (int i = 0; i < stack.size(); ++i)
				{
					if (stack[i] == ballroom - 1)
					{
						// Show path
						std::cout << "Trip can be started from node " << stack[0] + 1 << " and path will be:\n ";
						std::for_each(stack.begin(), stack.end(), [](const auto e) {std::cout << e + 1 << " -> "; });
						std::cout << stack[0] + 1 << std::endl;
						break;
					}
				}
				break;
			}
		}
	}
}

/// <summary>
/// Amount of nodes with degree more than 1
/// </summary>
/// <param name="matrix"></param>
int MaxSize(const Matrix& matrix)
{
	// Variable for calculations
	int max = 0;

	// Incremetation of the max variable every time sum of elements in row is bigger than 1
	for (int i = 0; i < matrix.size(); ++i)
		if (1 < std::accumulate(matrix[i].begin(), matrix[i].end(), 0))
			++max;

	return max;
}

/// <summary>
/// Writes matrix into the console
/// </summary>
/// <param name="matrix"></param>
void readMatrix(const Matrix& matrix)
{
	for (const auto e : matrix)
	{
		for (const auto e2 : e)
			std::cout << e2 << " ";
		std::cout << std::endl;
	}
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
	std::cout << "\nBall room is in " << ballRoom << " node.\n\n";

	// Setup some algorithm variables
	std::vector <bool> visited(matrix.size());
	std::vector <int> stack(MaxSize(matrix));
	std::fill(visited.begin(), visited.end(), false);

	for (int firstTop = 0; firstTop < matrix.size(); ++firstTop)
		DFS(matrix, firstTop, stack, visited, ballRoom, 0);

	system("pause");
	return 0;
}