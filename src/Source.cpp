#include "FileService.h"

#include <iostream>
#include <vector>

static int counter;
static bool IF_FIND;
void DFS(Matrix matrix, int FirstTop, int CurrentTop, std::vector <int>& stack, std::vector <bool>& visited, int size, int Ballroom, int Iteration)
{

	stack[Iteration++] = CurrentTop;
	if (Iteration < size)
	{
		visited[CurrentTop] = true;
		for (int Next_Top = 0; Next_Top < matrix.size(); ++Next_Top)
		{
			if (matrix[CurrentTop][Next_Top] == 1)
			{
				if (!visited[Next_Top])
					DFS(matrix, FirstTop, Next_Top, stack, visited, size, Ballroom, Iteration);
			}
		}
		visited[CurrentTop] = false;
	}
	else
	{
		for (int Next_Top = 0; Next_Top < matrix.size(); ++Next_Top)
		{
			if (matrix[CurrentTop][Next_Top] == 1)
			{
				if (Next_Top == FirstTop)
				{
					counter++;
					bool tmp = false;
					for (int i = 0; i < stack.size(); i++)
					{
						if (stack[i] == Ballroom - 1)
							tmp = true;
					}
					if (tmp)
					{
						if (counter == 1)
						{
							IF_FIND = true;
							std::cout << "Wycieczke mozemy rozpoczac w punkcie: " << FirstTop + 1 << std::endl;
							for (int i = 0; i < size; i++)
							{
								std::cout << stack[i] + 1 << " ";
							}
							std::cout << FirstTop + 1 << std::endl;
						}
						else
						{
							counter = 0;
						}
					}
				}
			}
		}
	}
	Iteration--;
}

int MaxSize(Matrix& matrix)
{
	std::vector <int> maxSize(matrix.size());
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)
		{
			maxSize[i] += matrix[i][j];
		}
	}

	int max = 0;
	for (int i = 0; i < matrix.size(); ++i)
	{
		if (maxSize[i] > 1)
			max++;
	}
	return max;
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
	Matrix matrix;
	int ballRoom = -1;

	readFile(ballRoom, matrix);

	for (const auto e : matrix)
	{
		for (const auto e2 : e)
			std::cout << e2 << " ";
		std::cout << std::endl;
	}

	std::vector <bool> visited(matrix.size());
	std::vector <int> stack(MaxSize(matrix));

	for (int i = 0; i < matrix.size(); i++)
	{
		visited[i] = false;
		stack[i] = 0;
	}
	std::cout << std::endl;
	for (int FirstTop = 0; FirstTop < matrix.size(); ++FirstTop)
	{
		int SecondTop = FirstTop;

		DFS(matrix, FirstTop, SecondTop, stack, visited, MaxSize(matrix), ballRoom, 0);
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

	return 0;
}