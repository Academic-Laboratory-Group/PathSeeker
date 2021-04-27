#include <iostream>
#include <array>
#include <vector>
#include <stack>

using Matrix = std::array<std::array <int, 5>, 5>;

bool DFS(Matrix& matrix, int FirstTop, int CurrentTop, std::stack <int> &stack, std::array <bool, 5>& visited)
{
	visited[CurrentTop] = true;
	
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
				if ((!visited[Next_Top]))
				{
					if(DFS(matrix, FirstTop, Next_Top, stack, visited))
						return true;
				}
				stack.pop();
				
			}

		}
	}
	

	return false;
}

int main()
{
	int Ballroom = 3;
	
	Matrix matrix{
	{
	   {0,1,0,0,1},
	   {1,0,1,1,1},
	   {0,1,0,1,1},
	   {0,1,1,0,0},
	   {1,1,1,0,0}
	}
	};

	std::stack<int> mystack;
	std::stack<int> mystack2;
	std::array <bool, matrix.size()> visited;;

	for (int FirstTop = 0; FirstTop < matrix.size(); ++FirstTop)
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			visited[i] = false;
		}

		mystack.push(-1);

		if (DFS(matrix, FirstTop, FirstTop, mystack, visited))
		{
			std::cout << "stos" << std::endl;
			
			while (!mystack.empty())
			{
				mystack2.push(mystack.top());
					mystack.pop();
			}

			while (!mystack2.empty())
			{
				int tmp = mystack2.top();
				mystack2.pop();
				if (tmp > -1)
					std::cout <<  tmp + 1 << " " ;
			}
			std::cout << FirstTop + 1 << std::endl;
		}
	}
	return 0;
}
