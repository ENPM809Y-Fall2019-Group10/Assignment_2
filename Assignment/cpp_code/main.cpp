#include <iostream>
#include <fstream>
#include <iomanip>
#include "include/scenario.h"

/* This function is to read vertices from the input file */
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

bool askStartGoalLocations(int& startX, int& startY, int& goalX, int& goalY, Scenario* maze)
{
	std::cout << "Enter the 'Start' location in the row,column format" << "\n";
	
	std::cin >> startX >> startY;
	if ( not maze->checkValidLocation(startX, startY) )		// Check validity location of the input
	{
		std::cout << "Input location is invalid. Please re-enter valid input location." << "\n";
		std::cout << "Note: Input location must be within " << "[0-" << maze->getLength()-1 << "," << "0-" << maze->getWidth()-1 << "], inclusive." << "\n";
		return false;
	}
	
	std::cout << "Enter the 'Goal' location in the row,column format" << "\n";
	
	std::cin >> goalX >> goalY;
	if ( not maze->checkValidLocation(goalX, goalY) )		// Check validity location of the input
	{
		std::cout << "Input location is invalid. Please re-enter valid input location." << "\n";
		std::cout << "Note: Input location must be within " << "[0-" << maze->getLength()-1 << "," << "0-" << maze->getWidth()-1 << "], inclusive." << "\n";
		return false;
	}
	return true;
}

bool findPath(int x, int y, const int& gx, const int& gy, Scenario* maze)
{
	if ( x==gx && y==gy ) return true;		// Check if location is at Goal
	
	if ( not maze->checkValidLocation(x, y) ) return false;		// check validity of x, y
	
	maze->markLocation(x, y);
	
	maze->printScenario(); std::cout << "\n";
	
	if ( findPath(x-1, y, gx, gy, maze) ) return true;	 // North move
	
	if ( findPath(x, y+1, gx, gy, maze) ) return true;	 // East move
	
	if ( findPath(x+1, y, gx, gy, maze) ) return true;	 // South move
	
	if ( findPath(x, y-1, gx, gy, maze) ) return true;	 // West move
	
	maze->unmarkLocation(x, y);
	
	return false;
}

int main(int argc, char **argv)
{
	printf("hello world\n");
	std::string path = "/home/rachith/git/ENPM809Y/Assignment2/Assignment/maze.txt";
	
	Scenario maze; 				// Define a maze
	readMap(path, &maze);		// Creating a layout for maze in binary format; 1-free space, 0-obstacle
		
	maze.printScenario();		// Print the maze read from file for verification!!
		
	std::cout << maze.getLength() << "\n";		// Print length of the maze
	std::cout << maze.getWidth() << "\n";		// Print width of the maze
	
	int startX{1}, startY{1}, goalX{1}, goalY{4};
	if ( askStartGoalLocations(startX, startY, goalX, goalY, &maze) )
	{
		std::cout << "Cool!, Now Let's see how to navigate!" << "\n";
		if ( findPath(startX, startY, goalX, goalY, &maze) ) std::cout << "Goal Reached!!" << "\n";
		else std::cout << "Unfortunately could not reach the Goal! :( ... Better luck next time ;)" << "\n";
	}
	else std::cout << "Exiting..." << "\n"; 
		
	maze.printFinalScenario();	// Print the maze after navigation!!
	
	return 0;
}
