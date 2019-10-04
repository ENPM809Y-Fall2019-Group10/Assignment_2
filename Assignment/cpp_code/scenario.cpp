#include "include/scenario.h"
#include <iostream>

void Scenario::constructScenario(int x, int y, int val)
{
	maze[x][y] = val;
}

int Scenario::getLength()
{
	return maze.size();
}

int Scenario::getWidth()
{
	return maze.at(0).size();
}

bool Scenario::checkValidLocation(int x, int y)
{
	if ( x>getLength()-1 || x<0 || y>getWidth()-1 || y<0 || maze[x][y]==0 || maze[x][y]==2 || maze[x][y]==3) return false;
	return true;
}

void Scenario::markLocation(int x, int y)
{
	maze[x][y] = 2;
}

void Scenario::unmarkLocation(int x, int y)
{
	maze[x][y] = 3;
}

void Scenario::printScenario()
{
	for(auto it = maze.begin(); it != maze.end(); ++it)
	{
		for (auto jt = it->second.begin() ; jt != it->second.end(); ++jt)
		{
			std::cout << maze[it->first][jt->first] << " ";
		}
		std::cout << "\n";
	}
}

void Scenario::printFinalScenario()
{
	for(auto it = maze.begin(); it != maze.end(); ++it)
	{
		for (auto jt = it->second.begin() ; jt != it->second.end(); ++jt)
		{
			if ( maze[it->first][jt->first]==0 )
			{
				std::cout << "# "; 
			}
			else if ( maze[it->first][jt->first]==1 || maze[it->first][jt->first]==3 )
			{
				std::cout << "  ";
			}
			else
			{
				std::cout << "+ ";
			}
		}
		std::cout << "\n";
	}
}