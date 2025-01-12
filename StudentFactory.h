#pragma once
#include "UndergraduateStudent.h"
#include "GraduateStudent.h"
#include "Student.h"
#include "Course.h"

class StudentFactory
{
public:
	StudentFactory();

	Student* CreateStudent(string type, int sid, Course* course);


};

