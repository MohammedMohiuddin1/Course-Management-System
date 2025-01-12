#include "InstructorFactory.h"

InstructorFactory::InstructorFactory()
{

}

//=============================================================================
//                            CreateInstructor()
// takes in a type, and id, and creates an instructor
//=============================================================================
Instructor* InstructorFactory::CreateInstructor(string type, int id)
{
	Instructor* instructorPtr; //ptr

	if (type == "F") //faculty specifer
	{

		instructorPtr = new Faculty(id);

		return instructorPtr;
	}
	if (type == "GI")//graduate instructor specifier
	{
		instructorPtr = new GraduateStudent(id);
		return instructorPtr;
	}
	return nullptr;
	

}
