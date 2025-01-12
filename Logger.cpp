#include "Logger.h"

//set to nullptr
Logger* Logger::LoggerPtr = nullptr;


Logger::~Logger()
{
}

//=============================================================================
//                            getInstance()
// ensurse that one single instance of the object gets passed
//=============================================================================
Logger* Logger::getInstance()
{
	if (LoggerPtr == nullptr)//if the instance doesnt exist then create it and return
	{
		LoggerPtr = new Logger();
		return LoggerPtr;

	}
	else //return it
	{
		return LoggerPtr;
	}
	return nullptr; //return null as last resort
}

//=============================================================================
//                            LogActions()
// takes in a message from the methods and logs them as successful or failed
//=============================================================================
void Logger::LogActions(string action, string status)
{
	FileWriter.open("Log.txt", ios_base::app);
	FileWriter << action << " " << status << endl;
	FileWriter.close();
}


Logger::Logger()
{
	FileWriter.open("Log.txt", ios_base::out);
	FileWriter.close();
}

