#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

//Reading a '.txt' file and creating a binary maze.
int (*(BinaryGraph)())[31]
{
	//Variable Declaration
	//array<array<int,46>,31> 
	static int BinMaze[46][31]; 
	ifstream inputdata;
	
	//" This should be the path of your 'Maze.txt' file, please change it "
	inputdata.open("/home/prasanna/Projects/Semester3/ENPM809Y/HomeWorks/HW2/maze.txt");
	char data;
	int i{0}, j{30};

	while(!inputdata.eof()) 
	{
		inputdata.get(data);

		if (data == '\n')
		{
			i=0;
			j-=1;
		}
		if (data == ' ')
		{
			BinMaze[i][j] =0;
			//cout<<'S'<<i<<j<<endl;
			i+=1;
		}
		else if(data=='#')
		{
			BinMaze[i][j] =1;
			//cout<<'B'<<i<<j<<endl;
			i+=1;
		}
		//cout<<"i: "<<i<<" ;"<<"j: "<<j<<endl;
	}
	inputdata.close();
	
	//cout<<"i"<<i<<" ;"<<"j"<<j<<endl;
	//cout <<"inny"<< BinMaze[3][29]<<endl;
	return BinMaze;
}

//Function to write to the text file
int writetotext(int Maze[46][31], int sx,int sy,int gx,int gy)
{
	//cout <<"betty"<< Maze[3][29]<<endl;
	ofstream outputdata;
	
	// "This is the new file that will be generated, please change the suitable file path "
	outputdata.open("/home/prasanna/Projects/Semester3/ENPM809Y/HomeWorks/HW2/SolutionFile.txt");
	
	for (int i=(30);i>=0;i--)
		{
			for(int j=0;j<=45;j++)
			{
				if ((j==sx) && (i==sy))
				{
					outputdata <<"S";
				}
				else if ((j==gx) && (i==gy))
				{
					outputdata <<"G";
				}
					
				else if(Maze[j][i]==0)
				{
					//cout <<"betty"<< Maze[3][29]<<endl;
					outputdata <<" ";
				}
				else if(Maze[j][i]==1)
				{
					outputdata <<"#";
				}
				else if (Maze[j][i]==3)
				{
					outputdata <<"+";
				}
				
			}
			outputdata<<'\n';
		
		}

	outputdata.close();
	return 0;
}

int count=0;

//Function FindPath
bool FindPath(int x, int y,int gx,int gy, int BinMaze[46][31], int sx,int sy)
{
	
	
	if((BinMaze[x][y]!=1) &&(BinMaze[x][y]!=3))
		{
		//cout<<x<<' '<<y<<endl;
		}
	
	//Function starts
	if (x<0||x>45||y<0||y>30) //outside of the maze then
	{
		//cout<<"Flag 1"<<endl;
		return false;
	}
	
	if (x==gx && y==gy) //is goal then
	{
		//cout<<"Flag 2"<<endl;
		writetotext(BinMaze,sx,sy,gx,gy);
		return true;
	}

	if ((BinMaze[x][y]==1)||(BinMaze[x][y]==3)) //is obstacle then
	{
		//cout<<"Flag 3"<<endl;
		return false;
	}

	//Mark (x,y) as part of the solution path
	BinMaze[x][y]=3;

	if (FindPath(x,y+1, gx,gy, BinMaze,sx,sy)) //is true then
	{
		//cout<<"Flag 4"<<endl;
		//BinMaze[x][y]=3;
		return true;
	}

	if (FindPath(x+1,y, gx,gy, BinMaze,sx,sy)) //is true then
	{
		//cout<<"Flag 5"<<endl;
		//BinMaze[x][y]=3;
		return true;
	}

	if (FindPath(x,y-1, gx,gy, BinMaze,sx,sy)) //is true then
	{
		//cout<<"Flag 6"<<endl;
		//BinMaze[x][y]=3;
		return true;
	}

	if (FindPath(x-1,y, gx,gy, BinMaze,sx,sy)) //is true then
	{
		//cout<<"Flag 7"<<endl;
		//BinMaze[x][y]=3;
		return true;
	}

	//Unmark (x,y) as part of the solution path
	BinMaze[x][y]=3;
	//cout<<"Flag 8"<<endl;
	writetotext(BinMaze,sx,sy,gx,gy);
	return false;

}

//Main FunctionclTabCtrl
int main()
{
	//Variable Declaration

	//Step 1: Binary Map Generation
	int (*Maze)[31];
	Maze = BinaryGraph(); 
	//cout <<"outy"<< Maze[3][29]<<endl;
	//_Exit(0);
	
	//Step 2: Requesting the Start and Goal position from the user
	int sx{0},sy{0},gx{0},gy{0};
	start:
	cout<<"Please enter the Start Position(x y): ";
	cin>>sx>>sy;
	cout<<endl;
	if ((sx<0||sx>45||sy<0||sy>30)||Maze[sx][sy]==1)
		{
			cout<<"The Start position you entered is either on the obstacle or outside the boundary !!"<<'\n'<<"Again, ";
			goto start;
		}
	goal:
	cout<<"Please enter the Goal Position(x y): ";
	cin>>gx>>gy;
	cout<<endl;
	if ((gx<0||gx>45||gy<0||gy>30)||Maze[gx][gy]==1)
		{
			cout<<"The Goal position you entered is either on the obstacle or outside the boundary !!"<<'\n'<<"Again, ";
			goto goal;
		}

	//Step 3: 
	bool Path = FindPath(sx,sy,gx,gy,Maze,sx,sy);
	//cout <<"outy"<< Maze[3][29]<<endl;
	if (Path==true)
	{
		cout<<"Congratzz!! Goal is reached"<<endl;
		cout<<"Please verify the solution in the ' SolutionFile.txt' file that is generated in the folder."<<'\n'<<endl;
		
	}
	else
	{
		cout<<"No Solution Exists! Goal can't be reached"<<endl;
		cout<<"Please verify the solution in the ' SolutionFile.txt' file that is generated in the folder."<<'\n'<<endl;
	}
	return 0;

}

