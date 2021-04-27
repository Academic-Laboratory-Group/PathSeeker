#include <iostream>
#include <array>
#include <vector>
#include <stack>

using Matrix = std::array<std::array <int, 5>, 5>;

int sptr = 0;


bool IsVisited(std::vector <int> visited, int Top)
{
	for (int i = 0; i < visited.size(); ++i)
	{
		if (visited[i] == Top)
			return true;
	}
	return false;
}

bool DFS(Matrix& matrix, int FirstTop, int CurrentTop, std::stack <int>& stack, std::vector <int>& visited)
{
	visited.push_back(CurrentTop);

	for (int Next_Top = 0; Next_Top < matrix.size(); ++Next_Top)
	{
		if (matrix[CurrentTop][Next_Top] == 1)
		{
			if (Next_Top != stack.top())
			{
				stack.push(CurrentTop);
				if (Next_Top == FirstTop)
				{
					return true;
				}
				if (!IsVisited(visited, Next_Top) && DFS(matrix, FirstTop, Next_Top, stack, visited))
				{
					return true;
				}
				stack.pop();
			}
		}
	}
	return false;
}

void DFSHamilton(Matrix& matrix, int FirstTop, int CurrentTop, std::array <int, 5>& stack, std::array <bool, 5>& visited, int size)
{
	stack[sptr++] = CurrentTop;
	if (sptr < size)
	{
		visited[CurrentTop] = true;
		for (int Next_Top = 0; Next_Top < matrix.size(); ++Next_Top)
		{
			if (matrix[CurrentTop][Next_Top] == 1)
			{
				if (!visited[Next_Top])
					DFSHamilton(matrix, FirstTop, Next_Top, stack, visited, size);
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
					for (int i = 0; i < size; i++)
						std::cout << " " << stack[i] + 1;

					std::cout << " " << 1 + 1;
					std::cout << std::endl;
				}
			}
		}
	}
	sptr--;
}

int MaxSize(Matrix& matrix)
{
	std::array <int, 5> maxSize{};
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)
		{
			maxSize[i] += matrix[i][j];
		}
	}
	int y = 0;
	for (int i = 0; i < matrix.size(); ++i)
	{
		if (maxSize[i] > 1)
			y++;
	}
	return y;
}
int main()
{
	Matrix matrix{
	{
	   {0,0,0,0,1},
	   {0,0,0,1,1},
	   {0,0,0,1,0},
	   {0,1,1,0,1},
	   {1,1,0,1,0}
	}
	};

	std::array <bool, matrix.size()> visited;
	std::array <int, matrix.size()> mystack{};
	for (int i = 0; i < matrix.size(); i++)
	{
		visited[i] = false;
	}
	sptr = 0;
	//for (int FirstTop = 0; FirstTop < matrix.size(); ++FirstTop)
	//{
	//	visited.clear();

	//	mystack.push(-1);

	//	if (DFS(matrix, FirstTop, FirstTop, mystack, visited))
	//	{
	//		std::cout << "stos" << std::endl;
	//		std::cout << FirstTop + 1;
	//		while (!mystack.empty())
	//		{
	//			int tmp = mystack.top();
	//				mystack.pop();
	//				if (tmp > -1)
	//					std::cout << " " << tmp + 1;
	//				else
	//					std::cout << std::endl;
	//		}

	//	}
	//	else
	//	{
	//		mystack.pop();                 
	//		std::cout << " - no cycle\n";
	//	}
	//}
	
	DFSHamilton(matrix, 1, 1, mystack, visited, MaxSize(matrix));





	return 0;
}