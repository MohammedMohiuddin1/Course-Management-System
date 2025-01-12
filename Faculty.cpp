#include "Faculty.h"

//=============================================================================
//                            Constructor
// takes in an id
//=============================================================================
Faculty::Faculty(int id)
{
	faculty_id = id;
}

//=============================================================================
//                            Destructor
// attempts to deallocate all pointers and memory
//=============================================================================
Faculty::~Faculty()
{
	//tried to deallocate pointers in both vectors
	while (!current_teaching_courses.empty())
	{
		delete current_teaching_courses[current_teaching_courses.size() - 1];
		current_teaching_courses[current_teaching_courses.size() - 1] = nullptr;
		current_teaching_courses.pop_back();
	}
	while (!courses_taught.empty())
	{
		delete courses_taught[courses_taught.size() - 1];
		courses_taught[courses_taught.size() - 1] = nullptr;
		courses_taught.pop_back();
	}
}

//=============================================================================
//                            getID()
// return id
//=============================================================================
int Faculty::getID() const
{
	return faculty_id;
}

//=============================================================================
//                            getTeachingCourses()
// return current_teaching_courses
//=============================================================================
vector<Course*> Faculty::getTeachingCourses() const
{
	return current_teaching_courses;
}

//=============================================================================
//                            getCoursesTaughtHistory()
// return courses_taught
//=============================================================================
vector<Course*> Faculty::getCoursesTaughtHistory() const
{
	return courses_taught;
}

//=============================================================================
//                            Teach()
// given a course teaches it
//=============================================================================
bool Faculty::Teach(Course* course)
{
	if (current_teaching_courses.size() < 3)//faculty can teach at most 3 courses at a time
	{
		if (course->AddInstructor(faculty_id) == true) //if the course can add the instructor then update the vectors and return true
		{
			current_teaching_courses.push_back(course);
			courses_taught.push_back(course);
			return true;
		}
	}
	return false; //else return false
}

//=============================================================================
//                            StopTeaching()
// given a course, stops teaching it
//=============================================================================
bool Faculty::StopTeaching(Course* course)
{
	//loop thorugh vector and find the course
	for (int i = 0; i < current_teaching_courses.size(); i++)
	{
		if (current_teaching_courses[i] == course)//if its found then remove it accordingly
		{
			swap(current_teaching_courses[i], current_teaching_courses[current_teaching_courses.size()-1]);
			current_teaching_courses.pop_back();
			course->RemoveInstructor(faculty_id); //remove the instructor from the course and return true
			return true;
		}
	}
	return false; //else return false
}

//=============================================================================
//                            DropAllTeachingCourses()
// Drops all the teaching courses
//=============================================================================
bool Faculty::DropAllTeachingCourses()
{
	for (int i = 0; i < current_teaching_courses.size(); i++) //loops through
	{
		StopTeaching(current_teaching_courses[i]); //and stops teaching all the courses
	}
	if (current_teaching_courses.size() == 1) //accounts for the error where 1 course is left inside
	{
		StopTeaching(current_teaching_courses[0]);
	}
	current_teaching_courses.clear(); //clear just incase and return true
	return true;
}

//=============================================================================
//                            PrintCurrentlyTeachingCourses()
// helper method to be used by university to print all the currently teaching courses
//=============================================================================
void Faculty::PrintCurrentlyTeachingCourses()
{
	for (int i = 0; i < current_teaching_courses.size(); i++)
	{
		cout << "course: " << current_teaching_courses[i]->getCourseID() << endl;
	}
}

