#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>

int PathCheck(int CurrentX, int CurrentY, char NPos, char EPos, char SPos, char WPos)
{
    int Direction; //Direction case indicator to be returned to main function
    int k=0; //Arbitrary variable for loop count

    if(NPos!='#' && NPos!='-' && NPos!='+' && k==0){ //Check clear path to North direction
        Direction=1;
        if (NPos=='G'){ //Check if Goal is to the North
            Direction=5;
        }
        k++;
    }
    else if(EPos!='#' && EPos!='-' && EPos!='+' && k==0){ //Check clear path to the East direction
        Direction=2;
        if (EPos=='G'){ //Check if Goal is to the East
            Direction=5;
        }
        k++;
    }
    else if(SPos!='#' && SPos!='-' && SPos!='+' && k==0){ //Check clear path to the South direction
        Direction=3;
        if(SPos=='G'){ //Check if Goal is to the South
            Direction=5;
        }
        k++;
    }
    else if(WPos!='#' && WPos!='-' && WPos!='+' && k==0){ //Check clear path to the West Direction
        Direction=4;
        if(WPos=='G'){ //Ccheck if Goal is to the West
            Direction=5;
        }
        k++;
    }
    else if(CurrentX<0||CurrentX>30||CurrentY<0||CurrentY>45){ //If going out of bounds, perform a backtrack process.
        Direction=6;
    }
        
    return Direction; //Return int for path switch case
}

int main()
{
    //Call initial maze file to be imported to array
    std::string MazeStrings[31]; //Temporary array of strings after maze.txt file read
    std::string MazeLine; //Temporary string name for maze line read from file
    std::ifstream MazeFile; //Assigned name to open maze file
    std::array<std::array<char,45>,31> MazeArray; //Char array defined for maze characters
    MazeFile.open("/home/acf/Documents/ENPM809Y Files/Assignment 2/maze.txt"); //Opens maze.txt file to MazeFile
    
    if (!MazeFile) { //If condition for when maze file is not defined or found. Causes program to stop
        std::cout<< "Unable to open file Maze.txt file"<<std::endl;
        exit(1);   // call system to stop
    }

    for(int i=0; i<=30; i++){ //For loop to read maze.txt lines to array of strings
        std::getline(MazeFile,MazeLine); //using getline() to read MazeFile
        MazeStrings[i]=MazeLine; //Writing maze.txt lines to array of strings
    }
    
    for(int i=0; i<=30; i++){ //For loop to convert array of strings to full array of char to manipulate for maze
        for(int j=0; j<=45; j++){
            MazeArray[i][j]=MazeStrings[i][j]; //Converts maze line strings to array of individual char
        }
    }
    
    MazeFile.close(); //closing maze.txt file after read
    
    bool startcheck=false; bool goalcheck=false; //bool values to confirm start/goal validity
    
    int StartX; int StartY; //Start coordinate integers entered by user
    while(startcheck!=true){ //loop to check validity of user input start coordinates
        
        std::cout<<"Input starting coordinates for robot (X Range: 1-29)(Y Range: 1-44): "<<std::endl;
        std::cin>>StartX>>StartY; //User input of starting coordinates

        if(StartX<0||StartX>31||StartY<0||StartY>45){ //Check start coordinates within maze boundary
            std::cout<<"Starting Coordinates are out of maze boundaries."<<std::endl;
            std::cout<<"Input new starting coordinates."<<std::endl;
        }
        
        else if(MazeArray[StartX][StartY]=='#'){ //Check start coordinate is clear of obstacle
            std::cout<<"Starting Coordinate is on obstacle"<<"/n"<<"Input new starting coordinates"<<std::endl;
        }
        else{ //Start coordinate is acceptable. Start point assigned to maze array
            startcheck=true;
            MazeArray[StartX][StartY]='S';
        }
    }
    
    int GoalX; int GoalY; //Goal coordinate integers entered by user
    while(goalcheck!=true){ //Loop to check validity of goal coordinates
        std::cout<<"Input goal coordinates for robot (X Range: 1-29)(Y Range: 1-44): "<<std::endl;
        std::cin>>GoalX>>GoalY; //User input of goal coordinates
        
        if(GoalX<0||GoalX>31||GoalY<0||GoalY>45){ //Check goal coordinates within maze boundary
            std::cout<<"Goal Coordinates are out of the maze boundaries."<<std::endl;
            std::cout<<"Input new goal coordinates."<<std::endl;
        }
        else if(StartX==GoalX && StartY==GoalY){ //Check goal coordinates do not equal start point
            std::cout<<"Goal Coordinates are the same as Start Coordinates"<<std::endl;
            std::cout<<"Input new goal coordinates"<<std::endl;
        }
        else if(MazeArray[GoalX][GoalY]=='#'){ //Check goal coordinate is clear of obstacle
            std::cout<<"Goal Coordinate is on obstacle"<<"\n"<<"Input new goal coordinates"<<std::endl;
        }
        else{ //Goal Coordinate is acceptable. Goal point assigned to maze array 
            goalcheck=true;
            MazeArray[GoalX][GoalY]='G';
        }
    }
    
    int CurrentX; int CurrentY; //Defines current coordinate position
    CurrentX=StartX;
    CurrentY=StartY; //Assigns start coordiantes to "current" position
    std::vector<int> VisitedX; //Visited X coordinates
    std::vector<int> VisitedY; //Visited Y coordinates
    int PathLength; //Length of Visited Coordinate vectors
    
    bool PathEnd=false; //Bool to identify true case when path is completed.
    char NPos; char EPos; char SPos; char WPos; //Char parameters created to represent neighboring position to current position
    
    int r=0;
    while(PathEnd!=true){ //While loop to run path search as long as PathEnd is not true
        r++;
        NPos=MazeArray[CurrentX-1][CurrentY]; //Assigns North direction char from current position to NPos
        EPos=MazeArray[CurrentX][CurrentY+1]; //Assigns East direction char from current position to EPos
        SPos=MazeArray[CurrentX+1][CurrentY]; //Assigns South direction char from current position to SPos
        WPos=MazeArray[CurrentX][CurrentY-1]; //Assigns West direction char from current position to WPos
        
        int DirectCase = PathCheck(CurrentX, CurrentY, NPos, EPos, SPos, WPos);
        
        switch(DirectCase){
            case 1:
                CurrentX=CurrentX-1; CurrentY=CurrentY; //Move to next North position
                MazeArray[CurrentX][CurrentY]='+'; //Assign '+' to visited position
                VisitedX.push_back(CurrentX);
                VisitedY.push_back(CurrentY);
                break;
            case 2:
                CurrentX=CurrentX; CurrentY=CurrentY+1; //Move to next East position
                MazeArray[CurrentX][CurrentY]='+'; //Assign '+' to visited position
                VisitedX.push_back(CurrentX);
                VisitedY.push_back(CurrentY);
                break;
            case 3:
                CurrentX=CurrentX+1; CurrentY=CurrentY; //Move to next South position
                MazeArray[CurrentX][CurrentY]='+'; //Assign '+' to visited position
                VisitedX.push_back(CurrentX);
                VisitedY.push_back(CurrentY);
                break;
            case 4:
                CurrentX=CurrentX; CurrentY=CurrentY-1; //Move to next West position
                MazeArray[CurrentX][CurrentY]='+'; //Assign '+' to visited position
                VisitedX.push_back(CurrentX);
                VisitedY.push_back(CurrentY);
                break;
            case 5: //If goal is reached, end path seach loop and notify operator
                std::cout<<"A path to the goal has been discovered. See the maze solution "<<std::endl;
                PathEnd=true;
                break;
            case 6: //Case if robot is going out of maze bounds
//                if(CurrentX!=StartX && CurrentY!=StartY){
                    MazeArray[CurrentX][CurrentY]='-'; //Assign '-' to unusable path, if not Start point
                    CurrentX=VisitedX[PathLength-1]; CurrentY=VisitedY[PathLength-1]; //Escape dead end to previous visited point
                    VisitedX.pop_back();
                    VisitedY.pop_back(); //Delete last visited point
                    break;
//                }
//                break;
            default: //Case if robot is at deadend and has to backtrack
//                if(CurrentX!=StartX && CurrentY!=StartY){
                    MazeArray[CurrentX][CurrentY]='-'; //Assign '-' to unusable path, if not Start point
                    CurrentX=VisitedX[PathLength-1]; CurrentY=VisitedY[PathLength-1]; //Escape dead end to previous visited point
                    VisitedX.pop_back();
                    VisitedY.pop_back(); //Delete last visited point
                    break;
//                }
//                break;
        }
        PathLength=VisitedX.size();
    }
    
    for(int i=0; i<=30; i++){ //For loop to test maze output
        for(int j=0; j<=45; j++){
            std::cout<<MazeArray[i][j];
        }
        std::cout<<'\n';
    }
    
	return 0;
}
