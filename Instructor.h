#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Course.h"
using namespace std;
class Instructor
{
public:
	//All methods to be implemented by faculty and graduate student
	virtual ~Instructor() {};

	//Getters
	virtual int getID() const = 0;
	virtual vector<Course*> getTeachingCourses() const = 0;
	virtual vector<Course*> getCoursesTaughtHistory() const = 0;

	//Action methods
	virtual bool Teach(Course* course) = 0;
	virtual bool StopTeaching(Course* course) = 0;
	virtual bool DropAllTeachingCourses() = 0;
	virtual void PrintCurrentlyTeachingCourses() = 0;
private:
	int id;
	vector<Course*> current_courses;
	vector<Course*> courses_taught;
};
