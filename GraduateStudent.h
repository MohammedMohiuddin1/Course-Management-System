#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Course.h"
#include "Student.h"
#include "Instructor.h"
using namespace std;
class GraduateStudent : public Student, public Instructor
{
public:
	//Constructors/Destructor
	GraduateStudent(int sid, Course* course);
	GraduateStudent(int sid);
	~GraduateStudent();

	//Getter methods
	int getID() const;
	vector<Course*> getEnrolledCourses() const;
	vector<Course*> getCourseHistory() const;
	
	vector<Course*> getTeachingCourses() const;
	vector<Course*> getCoursesTaughtHistory() const;

	//Action methods (commenting in cpp)
	bool Enroll(Course* course);
	bool Drop(Course* course);
	bool Teach(Course* course);
	bool StopTeaching(Course* course);
	bool DropAllCourses();
	bool DropAllTeachingCourses();

	void PrintCurrentlyTakingCourses();
	void PrintCurrentlyTeachingCourses();

private:
	int id;
	vector<Course*> current_teaching_courses;
	vector<Course*> enrolled_courses;
	vector<Course*> courses_taken;
	vector<Course*> courses_taught;
};
