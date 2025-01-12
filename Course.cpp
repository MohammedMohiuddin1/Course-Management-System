#include "Course.h"

//=============================================================================
//                            Constructor()
// creates course given an id and type
//=============================================================================
Course::Course(int id, string type)
{
	course_id = id;
	course_type = type;
}

//=============================================================================
//                            Constructor()
// creates course given an id and type and prereq
//=============================================================================
Course::Course(int id, string type, int prereq_id)
{
	course_id = id;
	course_type = type;
	prerequisite_id = prereq_id;
}


Course::~Course()
{

}

//=============================================================================
//                            getCourseSize()
// returns courses size aka the number of students
//=============================================================================
int Course::getCourseSize() const
{
	return course.size();
}

//=============================================================================
//                            getCourseID()
// returns course id
//=============================================================================
int Course::getCourseID() const
{
	return course_id;
}

//=============================================================================
//                            getPrerequisiteID()
// returns course prerequisite id
//=============================================================================
int Course::getPrerequisiteID() const
{
	return prerequisite_id;
}

//=============================================================================
//                            getCourseType()
// returns course type
//=============================================================================
string Course::getCourseType() const
{
	return course_type;
}

//=============================================================================
//                            getInstructorID()
// returns instructor id
//=============================================================================
int Course::getInstructorID() const
{
	return instructor_id;
}

//=============================================================================
//                            getCourse()
// returns course itself
//=============================================================================
vector<int> Course::getCourse() const
{
	return course;
}

//=============================================================================
//                            AddStudent()
// given an id, adds a student to the course
//=============================================================================
bool Course::AddStudent(int id)
{
	if (course.size() < 40) //checks because a course cant have more than 40 students
	{
		course.push_back(id); //if there is < 40 then add student and return true
		return true;
	}
	return false; //else return false
	
}

//=============================================================================
//                            RemoveStudent()
// given an id, removes a student from the course
//=============================================================================
bool Course::RemoveStudent(int id)
{
	//loops through course
	for (int i = 0; i < course.size(); i++)
	{
		if (course[i] == id) //finds the id of the student to remove and remove accordingly and return true
		{
			swap(course[i], course[course.size() - 1]);
			course.pop_back();
			return true;
		}
	}
	return false; //else return false
}

//=============================================================================
//                            AddInstructor()
// given an id, adds an instructor to the course
//=============================================================================
bool Course::AddInstructor(int id)
{
	if (instructor_id == -1) // I use -1 to indicate that the course doesnt have an instructor 
	{
		instructor_id = id; //if there is no instructor then add the instructor
		return true;
	}
	return false; //else if there is an instructor then return false
}

//=============================================================================
//                            RemoveInstructor()
// given an id, removes an instructor from the course
//=============================================================================
bool Course::RemoveInstructor(int id)
{
	instructor_id = -1; //sets to -1 to indicate that the course no longer has an instructor and returns true
	return true;
}

//=============================================================================
//                            PrintAllStudents()
// helper method to print all the students of a course
//=============================================================================
void Course::PrintAllStudents()
{
	for (int i = 0; i < course.size(); i++)
	{
		cout << "student: " << course[i] << endl;
	}
}

