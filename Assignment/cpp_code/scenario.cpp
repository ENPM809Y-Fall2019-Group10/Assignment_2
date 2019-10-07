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

void Scenario::markLocation(int x, int y, int z)
{
	maze[x][y] = z;
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

void Scenario::printFinalScenario(bool goalReached)
{
	for(auto it = maze.begin(); it != maze.end(); ++it)
	{
		for (auto jt = it->second.begin() ; jt != it->second.end(); ++jt)
		{
			switch ( maze[it->first][jt->first] )
			{
				case 0 : std::cout << "# "; break;
				case 1 : std::cout << "  "; break;
				case 2 : std::cout << "+ "; break;
				case 3 : if ( not goalReached ) std::cout<<"+ "; else std::cout<<"  "; break;
				case 5 : std::cout << "S "; break;
				case 6 : std::cout << "G "; break;
			}
		}
		std::cout << "\n";
	}
}