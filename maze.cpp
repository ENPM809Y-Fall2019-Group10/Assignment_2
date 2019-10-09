#include <iostream>
#include <string>
#include <vector>
using namespace std;



int main()
{
	int startx; ///< Initialize variable to store user input of x start position
	int starty;  ///< Initialize variable to store user input of y start position

	cout << "The maze looks like this:";
	displayMaze();
	char choice{};
	cout << "Would you like to use a different goal position than the predefined one? [Y/n]: ";
	cin >> choice;
	switch(choice) { // Switch that lets user choose how to select the goal position
		case 'N':
		case 'n':
		{
			goalX = nRows-1; goalY = nCols-1; // Save goal position as bottom right corner
			break;
		}
		case 'Y':
		case 'y':
		{
			maze[nRows-1][nCols-1]='.'; // 
			cout << "Please enter the goal position (x y): "; // Prompts user for the goal position.
			cin >> goalX >> goalY;
			// Checking for valid goal positions, if not valid, prompts user for different input.
			while(maze[goalX][goalY]=='#' || goalX<0 || goalX>nRows || goalY<0 || goalY>nCols) {
				cout << "Invalid placement of the goal position, please choose again." << endl;
				displayMaze();
				cout << "Please enter different coordinates for the goal position (x y): ";
				cin >> goalX >> goalY;
			}
			maze[goalX][goalY]='G';
			break;
		}
		default:
		{
			cout << "That is not a valid input, predefined goal defaulted.\n";
			goalX = nRows-1; goalY = nCols-1;
		}
	}

	// User inputs for the start position coordinates.
	cout << "Please enter the start position (x y): ";
	cin >> startx >> starty;
	// Checking for valid start positions, if not valid, prompts user for different input.
	while(maze[startx][starty]=='#' || startx<0 || startx>=nRows || starty<0 || starty>=nCols) {
		cout << "Invalid placement of the start position, please choose again." << endl;
		displayMaze();
		cout << "Please enter different coordinates for the start position (x y): ";
		cin >> startx >> starty;
	}

	maze[startx][starty]='S'; // Prints 'S' on maze for display purposes
	cout << "\nThe maze to be solved:";
	displayMaze();
	maze[startx][starty]='.'; // Removes 'S' from maze after displayed

	findPath(startx,starty); // Runs recursive function to solve maze
	if(maze[startx][starty]=='+') {
		cout << "\nThere exists a path from the start to the goal position!!" << endl;
		maze[startx][starty]='S';
		cout << "\nThe maze solution path looks like this: " << endl;
		cout << "Starting Position: " << "[" << startx << "," << starty << "]\n";
		// This loop outputs the movements made on the solution path:
			// the loop runs through the vector backwards,
			// since the recursive function saves the data in reverse order
		for (int i=sizePathTaken-1; i > -1; --i) {
			cout << movements[i] << ": "; // Action string
			cout << "[" << pathTaken[i][0] << "," << pathTaken[i][1] << "]" << endl;
		}
		cout << "The Goal is reached!" << endl;
		displayMaze();
		mazePathDisplay(); // This displays the maze path without wrong turns
	}
	else
		cout << " No path can be found!! :(\n" << endl;
	return 0;
}


bool obstacleCheck(int x,int y,vector<vector<char>> maze)
{
	if(maze[x][y]=='#' || maze[x][y]=='+')
		return true;
	return false;
}

bool outsideMaze(int x,int y)
{
	if(x<0 || x>=nRows || y<0 || y>=nCols) {
		return true;
	}
	return false;
}


bool goalCheck(int x,int y,int goalX,int goalY)
{
	if(x==goalX && y==goalY)
		return true;
	return false;
}


vector<int> goNorth(int x,int y)
{
	x=x-1;
	y=y;
	vector<int> north{x,y};
	return north;
}

vector<int> goSouth(int x,int y)
{
	x=x+1;
	y=y;
	vector<int> south{x,y};
	return south;
}

vector<int> goEast(int x,int y)
{
	x=x;
	y=y+1;
	vector<int> east{x,y};
	return east;
}

vector<int> goWest(int x,int y)
{
	x=x;
	y=y-1;
	vector<int> west{x,y};
	return west;
}


bool findPath(int x,int y)
{
	if(outsideMaze(x,y))
		return false;
	if(obstacleCheck(x,y,maze))
		return false;
	if(goalCheck(x,y,goalX,goalY))
		return true;

	vector<int> movePos;
	maze[x][y]='+';
	if (findPath(goNorth(x,y)[0],goNorth(x,y)[1])) {
		movePos = goNorth(x,y); // Obtain [north] position index
		pathTaken.push_back(movePos); // Add [north] position to movement vector
		sizePathTaken = pathTaken.size(); // Update size of pathTaken
		movements.push_back("Moved North"); // Add action string to vector
		return true;
	}
	if (findPath(goEast(x,y)[0],goEast(x,y)[1])) {
		movePos = goEast(x,y);
		pathTaken.push_back(movePos);
		sizePathTaken = pathTaken.size();
		movements.push_back("Moved East");
		return true;
	}
	if (findPath(goSouth(x,y)[0],goSouth(x,y)[1])) {
		movePos = goSouth(x,y);
		pathTaken.push_back(movePos);
		sizePathTaken = pathTaken.size();
		movements.push_back("Moved South");
		return true;
	}
	if (findPath(goWest(x,y)[0],goWest(x,y)[1])) {
		movePos = goWest(x,y);
		pathTaken.push_back(movePos);
		sizePathTaken = pathTaken.size();
		movements.push_back("Moved West");
		return true;
	}
	// If no movement can be made, we must backtrack.
	maze[x][y]='x';
	return false;
}


void displayMaze() {
	cout << "\n     "; // Prepares first line
	for (int j=0; j<nCols; ++j)
		cout << j << " "; // This loop displayes the column maze numbering
	cout << "\n   ---";
	for (int j=0; j<nCols; ++j)
		cout << "--"; // This loop displays the upper maze boundary based on its size
	for (int i=0; i<nRows; ++i) {
		cout << "\n " << i << " | "; // This loop displayes the row maze numbering
		for (int j=0; j<nCols; ++j)
			cout << maze[i][j] << " "; // This loop displayes the actual maze characters
		cout << "|";
	}
	cout << "\n   ---";
	for (int j=0; j<nCols; ++j)
		cout << "--"; // This loop displays the lower maze boundary based on its size
	cout << endl;
}


void mazePathDisplay() {
	for (int i=0; i<nRows; i++) {
		for (int j=0; j<nCols; j++) {
			// If the maze contains a wrong turn 'x'
			if(maze[i][j]=='x') {
				// Then replace each 'x' with a '.'
				for (int i=0; i<nRows; i++) {
					for (int j=0; j<nCols; j++) {
						if(maze[i][j]=='x')
							maze[i][j]='.';
					}
				}
				cout << "\nThe maze path displayed without wrong paths taken:";
				displayMaze();
				return;
			}
		}
	}
}
