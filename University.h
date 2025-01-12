#pragma once
#include "Course.h"
#include "Faculty.h"
#include "GraduateStudent.h"
#include "UndergraduateStudent.h"
#include "Logger.h"
#include "StudentFactory.h"
#include "InstructorFactory.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

class University
{
public:
	//Constructor/Destructor
	University();
	~University();

	//Action Methods (commenting in cpp)
	bool AddCourse(int id, string type);
	bool AddCourseWithPreReq(int id, string type, int pid);
	bool RemoveCourse(int id);

	bool AddStudent(int sid, string type, int cid);
	bool RemoveStudent(int sid);

	bool AddInstructor(int id, string type);
	bool RemoveInstructor(int id);

	bool AssignToStudent(int student_id, int course_id);
	bool RemoveFromStudent(int student_id, int course_id);

	bool AssignToInstructor(int instructor_id, int course_id);
	bool RemoveFromInstructor(int instructor_id, int course_id);

	//Printing Methods (commenting in cpp)
	void PrintStudentHistory(int type, int sid);

	void PrintCourseHistory(int type, int cid);

	void PrintInstructorHistory(int type, int id);

	void PrintAllStats(int type);


	//Delete method (commenting in cpp)
	void DeleteUniversity();


private:
	vector<Course*> courses;
	vector<Student*> students;
	vector<Instructor*> instructors;
	Logger* logger = Logger::getInstance();


};
