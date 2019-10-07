#include <iostream>
#include <fstream>
#include <iomanip>
#include "include/scenario.h"

/* This function is to reads the maze from the input file */
void readMap(std::string path, Scenario* maze)
{
	std::string line; 	// each line in file	
	std::ifstream myFile (path); // file to be read
	
	if (myFile.is_open())
	{	
		int lineNumber = 0;
		while (getline (myFile,line))
		{			
			// Start reading the line
			int characterNum = 0;
			for (char c : line)
			{
				if ( c == '#' )
				{
					maze->constructScenario(lineNumber, characterNum, 0);
				}
				else
				{
					maze->constructScenario(lineNumber, characterNum, 1);
				}
				characterNum++;
			}
			lineNumber++;
		}
		myFile.close();
	}
	else std::cout << "Unable to open the file" << "\n";
}

void askStartGoalLocations(int& startX, int& startY, int& goalX, int& goalY, Scenario* maze)
{
	// Read Start point
	std::cout << "Enter the 'Start' location in the row,column format" << "\n";
	bool startFlag = true;
	do{
		std::cin >> startX >> startY;
		if ( not maze->checkValidLocation(startX, startY) )		// Check validity location of the input
		{
			std::cout << "Input location is invalid. Please re-enter valid input location." << "\n";
			std::cout << "Note: Input location must be within " << "[0-" << maze->getLength()-1 << "," << "0-" << maze->getWidth()-1 << "], inclusive." << "\n";
			std::cout << "Please input again\n";
			startFlag = false;
		}
		else startFlag = true;
	}while ( not startFlag );
	
	// Read Goal point
	std::cout << "Enter the 'Goal' location in the row,column format" << "\n";
	bool goalFlag = true;
	do{
		std::cin >> goalX >> goalY;
		if ( not maze->checkValidLocation(goalX, goalY) )		// Check validity location of the input
		{
			std::cout << "Input location is invalid. Please re-enter valid input location." << "\n";
			std::cout << "Note: Input location must be within " << "[0-" << maze->getLength()-1 << "," << "0-" << maze->getWidth()-1 << "], inclusive." << "\n";
			std::cout << "Please input again\n";
			goalFlag = false;
		}
		else goalFlag = true;
	}while ( not goalFlag );
	
	std::cout << "Cool!, Now Let's see how to navigate!" << "\n";
}

bool findPath(int x, int y, const int& gx, const int& gy, Scenario* maze)
{
	if ( x==gx && y==gy ) return true;		// Check if location is at Goal
	
	if ( not maze->checkValidLocation(x, y) ) return false;		// Check validity of x, y
	
	maze->markLocation(x, y, 2);		// Mark traversed point
	
//	maze->printScenario(); std::cout << "\n";
	
	if ( findPath(x-1, y, gx, gy, maze) ) return true;	 // North move
	
	if ( findPath(x, y+1, gx, gy, maze) ) return true;	 // East move
	
	if ( findPath(x+1, y, gx, gy, maze) ) return true;	 // South move
	
	if ( findPath(x, y-1, gx, gy, maze) ) return true;	 // West move
	
	maze->markLocation(x, y, 3);		// Mark ineligible point
	
	return false;
}

int main(int argc, char **argv)
{
	
	std::string path = "/home/rachith/git/ENPM809Y/Assignment2/Assignment/maze.txt";
	
	Scenario maze; 				// Define a maze object
	readMap(path, &maze);		// Creating a layout for maze in binary format; 1-free space, 0-obstacle
		
	maze.printScenario();		// Print the maze read from file for verification!!
	
	int startX{1}, startY{1}, goalX{1}, goalY{4};		// Define start and goal variables
	
	askStartGoalLocations(startX, startY, goalX, goalY, &maze);		// Collect start and goal locations from user
	
	bool goalReached = false;
	
	if ( findPath(startX, startY, goalX, goalY, &maze) ){
		std::cout << "Goal Reached!!" << "\n";
		goalReached = true;
	}
	else std::cout << "Unfortunately 'Path Not Found' :( ... Better luck next time ;)" << "\n";
	
	maze.markLocation(startX, startY, 5);		// Mark Start Point
	maze.markLocation(goalX, goalY, 6);		// Mark Goal Point

	maze.printFinalScenario(goalReached);	// Print the maze after navigation!!
	
	return 0;
}
