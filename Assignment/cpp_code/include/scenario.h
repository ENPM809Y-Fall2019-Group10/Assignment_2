#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <map>

class Scenario{
private:
	std::map< int, std::map<int, int> > maze;
public:
	void constructScenario(int, int, int);
	int getLength();
	int getWidth();
	bool checkValidLocation(int, int);
	void markLocation(int, int, int);
	void printScenario();
	void printFinalScenario(bool);
};

#endif