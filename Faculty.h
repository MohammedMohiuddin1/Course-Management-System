#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Course.h"
#include "Instructor.h"
using namespace std;

class Faculty : public Instructor
{
public:

	//Constructor/Destructor
	Faculty(int id);
	~Faculty();

	//Getter methods
	int getID() const;
	vector<Course*> getTeachingCourses() const;
	vector<Course*> getCoursesTaughtHistory() const;

	//Action Methods (commenting in cpp)
	bool Teach(Course* course);
	bool StopTeaching(Course* course);
	bool DropAllTeachingCourses();
	void PrintCurrentlyTeachingCourses();

private:
	//Private data members
	int faculty_id;
	vector<Course*> current_teaching_courses;
	vector<Course*> courses_taught;
};
