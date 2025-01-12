#include "UndergraduateStudent.h"

//=============================================================================
//                              Constructor()
// takes in an id and course and enrolls student into course
//=============================================================================
UndergraduateStudent::UndergraduateStudent(int sid, Course* course)
{
	id = sid;
	bool result = Enroll(course);
}

//=============================================================================
//                              Destructor()
// destructors and deallocates appropriately
//=============================================================================
UndergraduateStudent::~UndergraduateStudent()
{
	//tried to deallocate pointers in both enrolled and history vectors
	while (!enrolled_courses.empty())
	{
		delete enrolled_courses[enrolled_courses.size() - 1];
		enrolled_courses[enrolled_courses.size() - 1] = nullptr;
		enrolled_courses.pop_back();
	}
	while (!courses_taken.empty())
	{
		delete courses_taken[courses_taken.size() - 1];
		courses_taken[courses_taken.size() - 1] = nullptr; 
		courses_taken.pop_back();

	}
}

//=============================================================================
//                              getID()
// return id
//=============================================================================
int UndergraduateStudent::getID() const
{
	return id;
}

//=============================================================================
//                              getEnrolledCourses()
// return enrolled courses
//=============================================================================
vector<Course*> UndergraduateStudent::getEnrolledCourses() const
{
	return enrolled_courses;
}

//=============================================================================
//                              getCourseHistory()
// return courses_taken
//=============================================================================
vector<Course*> UndergraduateStudent::getCourseHistory() const
{
	return courses_taken;
}

//=============================================================================
//                              Enroll()
// takes in a course and enrolls
//=============================================================================
bool UndergraduateStudent::Enroll(Course* course)
{
	if (course->getPrerequisiteID() != -1)//check if the course has a prereq
	{
		bool prerequisite_completed = false; //create a bool to check if the prereq has been taken

		for (int k = 0; k < courses_taken.size(); k++) //loop through and check if the student has taken the prereq
		{
			if (courses_taken[k]->getCourseID() == course->getPrerequisiteID())//if they have
			{
				prerequisite_completed = true; //then set bool to true and continue enrolling as normal
				break;
			}
			if (prerequisite_completed == false) //else return false 
			{
				return false;
			}
		}
	}

	//if the course doesnt have a prereq then loop through the history to check if the student has taken the course before
	for (int i = 0; i < courses_taken.size(); i++)
	{
		if (courses_taken[i] == course)//if they have then return false
		{
			return false;
		}
	}
		if (course->getCourseType() == "UG") //if the course type is valid
		{
			if (course->AddStudent(id) == true) //and the course can add the student
			{
				enrolled_courses.push_back(course); //then add the course to enrolled courses and history and return true
				courses_taken.push_back(course);
				return true;
			}
		}
	
	return false;

}

//=============================================================================
//                              Drop()
// takes in a course and drops
//=============================================================================
bool UndergraduateStudent::Drop(Course* course)
{
	//find the course to drop
	for (int i = 0; i < enrolled_courses.size(); i++)
	{
		if (enrolled_courses[i] == course) //if its found then remove accordingly and remove the student from the course as well and return true
		{
			swap(enrolled_courses[i], enrolled_courses[enrolled_courses.size() - 1]);
			enrolled_courses.pop_back();
			course->RemoveStudent(id);
			return true;
		}
	}
	//if the course wasnt found return false
	return false;
}

//=============================================================================
//                              DropAllCourses()
// drops all courses
//=============================================================================
bool UndergraduateStudent::DropAllCourses()
{
	for (int i = 0; i < enrolled_courses.size(); i++) //loops through and drops all the courses
	{
		Drop(enrolled_courses[i]);
	}
	if (enrolled_courses.size() == 1) //had this error where there was still one left. make sure that gets accounted for
	{
		Drop(enrolled_courses[0]);
	}
	enrolled_courses.clear(); //clear just incase and return true
	return true;
}

//=============================================================================
//                              PrintCurrentlyTakingCourses()
// helper method used in university to print currently taking courses
//=============================================================================
void UndergraduateStudent::PrintCurrentlyTakingCourses()
{
	for (int i = 0; i < enrolled_courses.size(); i++)
	{
		cout << "course: " << enrolled_courses[i]->getCourseID() << endl;
	}
}

