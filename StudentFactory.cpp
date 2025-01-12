#include "StudentFactory.h"

StudentFactory::StudentFactory()
{

}

//=============================================================================
//                            CreateStudent()
// takes in a type, and id, and a course and creates a student
//=============================================================================
Student* StudentFactory::CreateStudent(string type, int id, Course* course)
{
	Student* studentPtr; //studenptr

	if (type == "UG") //undergrad student specifier
	{
		studentPtr = new UndergraduateStudent(id, course);
		return studentPtr;

	}
	else if (type == "G") //grad student specifier
	{
		studentPtr = new GraduateStudent(id, course);
		return studentPtr;
	}
	return nullptr;

}
