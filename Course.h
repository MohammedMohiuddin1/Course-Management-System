#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Course
{
public:
	
	//Constructors/Destructor
	Course(int id, string type);
	Course(int id, string type, int prereq_id);

	~Course();

	//Getter Methods
	int getCourseSize() const;
	int getCourseID() const;
	int getPrerequisiteID() const;
	string getCourseType() const;
	int getInstructorID() const;
	vector<int> getCourse() const;

	//Action Methods (commenting in cpp)
	bool AddStudent(int id);
	bool RemoveStudent(int id);
	bool AddInstructor(int id);
	bool RemoveInstructor(int id);
	void PrintAllStudents();

private:
	//Private data members: Note -1 indicates a null or empty status
	int prerequisite_id = -1;
	int instructor_id = -1;
	int course_id;
	string course_type;
	vector<int> course;
};
