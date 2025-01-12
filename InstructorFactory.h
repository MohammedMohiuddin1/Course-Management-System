#pragma once
#include "Faculty.h"
#include "GraduateStudent.h"
#include "Instructor.h"


class InstructorFactory
{
public:
	InstructorFactory();

	Instructor* CreateInstructor(string type, int id);


};

