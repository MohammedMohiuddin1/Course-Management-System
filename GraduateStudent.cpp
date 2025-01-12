#include "GraduateStudent.h"

//=============================================================================
//                              Constructor
// takes in an id and course and enrolls student into course
//=============================================================================
GraduateStudent::GraduateStudent(int sid, Course* course)
{
	id = sid;
	Enroll(course);
}

//=============================================================================
//                             Instructor Constructor
// takes in id
//=============================================================================
GraduateStudent::GraduateStudent(int sid)
{
	id = sid;
}

//=============================================================================
//                             Destructor
// Attempts to properly deallocate all the pointer objects in the vector
//=============================================================================
GraduateStudent::~GraduateStudent()
{
	//tried to deallocate pointers in all vectors
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

	delete current_teaching_courses[0];
	current_teaching_courses[0] = nullptr;
	current_teaching_courses.pop_back();

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
int GraduateStudent::getID() const
{
	return id;
}

//=============================================================================
//                            getEnrolledCourses()
// return enrolled courses
//=============================================================================
vector<Course*> GraduateStudent::getEnrolledCourses() const
{
	return enrolled_courses;
}

//=============================================================================
//                            getTeachingCourses()
// return current teaching courses
//=============================================================================
vector<Course*> GraduateStudent::getTeachingCourses() const
{
	return current_teaching_courses;
}

//=============================================================================
//                            getCourseHistory()
// return courses taken
//=============================================================================
vector<Course*> GraduateStudent::getCourseHistory() const
{
	return courses_taken;
}

//=============================================================================
//                            getCoursesTaughtHistory()
// return courses taught
//=============================================================================
vector<Course*> GraduateStudent::getCoursesTaughtHistory() const
{
	return courses_taught;
}

//=============================================================================
//                            Enroll()
// Takes in a course and enrolls it
//=============================================================================
bool GraduateStudent::Enroll(Course* course)
{
	//loop through history to make sure student hasnt taken the course
	for (int i = 0; i < courses_taken.size(); i++)
	{
		if (courses_taken[i] == course)
		{
			return false;
		}
	}

	for (int i = 0; i < courses_taught.size(); i++)
	{
		if (courses_taught[i] == course) //you cant enroll in a course you have taught before
		{
			return false;
		}
	}
	
		if (course->getCourseType() == "G")//check to make sure its valid type
		{
			if (course->AddStudent(id) == true) //make sure the student can be added to the course
			{
				enrolled_courses.push_back(course); //add to appropriate vectors and return true
				courses_taken.push_back(course);
				return true;
			}
		}
	//else return false
	return false;
}

//=============================================================================
//                            Drop()
// Takes in a course and drops it
//=============================================================================
bool GraduateStudent::Drop(Course* course)
{
	//find the course to drop
	for (int i = 0; i < enrolled_courses.size(); i++)
	{
		if (enrolled_courses[i] == course) //remove accordingly and remove the student from the course and return true
		{
			swap(enrolled_courses[i], enrolled_courses[enrolled_courses.size() - 1]);
			enrolled_courses.pop_back();
			course->RemoveStudent(id);
			return true;
		}
	}
	//else return false
	return false;
}

//=============================================================================
//                            Teach()
// Takes in a course and teaches it
//=============================================================================
bool GraduateStudent::Teach(Course* course)
{
	if (!enrolled_courses.size() == 0) //if there are enrolled courses
	{
		for (int i = 0; i < enrolled_courses.size(); i++) //a graduate cannot teach a course they are taking
		{
			if (enrolled_courses[i] == course) //if they are then return false
			{
				return false;
			}
		}
	}
	if (current_teaching_courses.size() == 0) //graduate can only teach 1 course at a time
	{
		if (course->AddInstructor(id) == true) //if the course can add the instructor then push back the course into the vectors and return true
		{
		current_teaching_courses.push_back(course);
		courses_taught.push_back(course);
		return true;
		}
	}
	//return false
	return false;
}

//=============================================================================
//                            StopTeaching()
// finds a course and stops teaching
//=============================================================================
bool GraduateStudent::StopTeaching(Course* course)
{
	current_teaching_courses.clear(); //Since GradStudent only ever teaches one course just clear the vector
	course->RemoveInstructor(id); //Remove the instructor of the course and return true
	return true;
}

//=============================================================================
//                            DropAllCourses()
// Drops all courses for the graduate student (this is the same thing as instructor)
//=============================================================================
bool GraduateStudent::DropAllCourses()
{
	for (int i = 0; i < enrolled_courses.size(); i++) //drop the courses from enrolled courses
	{
		Drop(enrolled_courses[i]);
	}
	if (enrolled_courses.size() == 1) //off by one edge case being addressed
	{
		Drop(enrolled_courses[0]);
	}
	enrolled_courses.clear(); //clear jus incase and return true
	return true;
}

//=============================================================================
//                            DropAllTeachingCourses()
// Drops all teaching courses for the graduate student (this is the same thing as instructor)
//=============================================================================
bool GraduateStudent::DropAllTeachingCourses()
{
	StopTeaching(current_teaching_courses[0]); //since its only one course, you just drop it and return false
	return false;
}

//=============================================================================
//                            PrintCurrentlyTakingCourses()
// helper method for university to print currently taking courses
//=============================================================================
void GraduateStudent::PrintCurrentlyTakingCourses()
{
	for (int i = 0; i < enrolled_courses.size(); i++)
	{
		cout << "course: " << enrolled_courses[i]->getCourseID() << endl;
	}
}

//=============================================================================
//                            PrintCurrentlyTeachingCourses()
// helper method for university to print currently teaching courses
//=============================================================================
void GraduateStudent::PrintCurrentlyTeachingCourses()
{
	if (!current_teaching_courses.empty())
	{
		cout << "course: " << current_teaching_courses[0]->getCourseID() << endl;
	}
	
}
