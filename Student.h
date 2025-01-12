#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Course.h"
using namespace std;
class Student
{
public:
	//Methods to be implemented by Graduate Students and Undergraduate Students
	virtual ~Student() {};

	//Getters
	virtual int getID() const = 0;
	virtual vector<Course*> getEnrolledCourses() const = 0;
	virtual vector<Course*> getCourseHistory() const = 0;

	//Action Methods (commenting in cpp)
	virtual bool Enroll(Course* course) = 0;
	virtual bool Drop(Course* course) = 0;
	virtual bool DropAllCourses() = 0;
	virtual void PrintCurrentlyTakingCourses() = 0;
	

private:
	int id;
	vector<Course*> enrolled_courses;
	vector<Course*> courses_taken;

};
