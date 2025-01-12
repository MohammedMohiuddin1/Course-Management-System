#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Course.h"
#include "Student.h"
using namespace std;
class UndergraduateStudent : public Student
{
public:
	//Constructor/Destructor
	UndergraduateStudent(int id, Course* course);
	~UndergraduateStudent();

	//Getter Methods
	int getID() const;
	vector<Course*> getEnrolledCourses() const;
	vector<Course*> getCourseHistory() const;

	//Action Methods (commenting in cpp)
	bool Enroll(Course* course);
	bool Drop(Course* course);
	bool DropAllCourses();
	void PrintCurrentlyTakingCourses();

private:
	int id;
	vector<Course*> enrolled_courses;
	vector<Course*> courses_taken;
};
