#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Logger
{
public:
	//Singleton Logger
	~Logger();

	//Getter Method
	static Logger* getInstance();

	//Action method (commenting in cpp)
	void LogActions(string action, string status);

	

private:
	//Private Constructor since its singleton and a static ptr
	Logger();
	static Logger* LoggerPtr;
	ofstream FileWriter;
};
