#include "University.h"

University::University()
{
}

//=============================================================================
//                               Destructor
//Deletes the university
//=============================================================================
University::~University()
{
	//DeleteUniversity();
}

//=============================================================================
//                               AddCourse
//creates a course that takes in an id and type (undergrad or grad) and adds 
//it to the university
//=============================================================================
bool University::AddCourse(int id, string type)
{
	//Loop through course to check if it exists in the university
	for (int i = 0; i < courses.size(); i++)
	{
		if (courses[i]->getCourseID() == id) //if it exists, log as failed and return false
		{
			logger->LogActions("Tried to add course NOT FOUND", "(Failed)");
			return false;
		}
	}
	Course* course = new Course(id, type); //Create a new course, push it back to the courses vector, log it as a success and return true
	courses.push_back(course);
	logger->LogActions("added course: " + to_string(id) + " type: " + type + " " + " courses size: " + to_string(courses.size()), "(Successful)");
	return true;
}

//=============================================================================
//                               AddCourseWithPreReq
//creates a course that takes in an id and type (undergrad or grad) and 
//a prerequisite course and adds it to the university
//=============================================================================
bool University::AddCourseWithPreReq(int id, string type, int pid)
{
	if (id == pid) //a course cannot be its own prerequisite
	{
		logger->LogActions("Tried to add course with prereq", "(Failed)"); //log as failed and return false;
		return false;
	}
	//Loop through and check to see if the course exists
	for (int i = 0; i < courses.size(); i++)
	{
		if (courses[i]->getCourseID() == id) //if it does, log as failed and return false
		{
			logger->LogActions("Tried to add course with prereq NOT FOUND", "(Failed)");
			return false;
		}
	}
	//else create a course with a prereq, push it back to the courses, log as success and return true
	Course* course = new Course(id, type, pid);
	courses.push_back(course);
	logger->LogActions("added course: " + to_string(id) + " type: " + type + " " + "with prereq: " + to_string(pid) + " courses size: " + to_string(courses.size()), "(Successful)");
	return true;
}


//=============================================================================
//                               RemoveCourse
// Given an id, finds a course and removes it
//=============================================================================
bool University::RemoveCourse(int id)
{
	//loop through courses
	for (int i = 0; i < courses.size(); i++)
	{
		//if the course is found, 
		if (courses[i]->getCourseID() == id) 
		{
			//loop through its students and make them drop the course
			for (int j = 0; j < students.size(); j++)
			{
				students[j]->Drop(courses[i]);
			}
			//loop thorugh the instructors and make them stop teaching the course
			for (int k = 0; k < instructors.size(); k++)
			{
				instructors[k]->StopTeaching(courses[i]);
			}
            //finally swap the course to be removed with the last index and popback. 
			swap(courses[i], courses[courses.size() - 1]);
			delete courses[courses.size() - 1];
			courses[courses.size() - 1] = nullptr;
			courses.pop_back();

			//log as a success and return true
			logger->LogActions("removed course: " + to_string(id) + " courses size: " + to_string(courses.size()), "(Successful)");
			return true;
		}
	}
	//if the course wasn't found log as failed, and return false
	logger->LogActions("Tried to remove course: " + to_string(id), "(Failed)");
	return false;
}

//=============================================================================
//                               AddStudent
// Creates a student using the factory and the given parameters and adds it to the 
// University.
//=============================================================================
bool University::AddStudent(int sid, string type, int cid)
{
	for (int i = 0; i < students.size(); i++) //check to see if the id given is an existing id
	{
		if (students[i]->getID() == sid) //if it is then the student cant be created, log as failed and return false;
		{
			logger->LogActions("Tried to add student: " + to_string(sid), "(Failed)");
			return false;
		}
	}
	//create a studentFactory object and Course* variable to create the student and store the course given.
	StudentFactory StudentCreator;
	Course* courseToTake = nullptr;

	//loop through and check if the course exists 
	for (int i = 0; i < courses.size(); i++)
	{
		if (courses[i]->getCourseID() == cid) //if it does check if it has space
		{
			if (courses[i]->getCourseSize() < 40) //if it has space then set the course to the appropriate course and break out of the loop
			{
				courseToTake = courses[i];
				break;
			}
			else //if the course is full log as failed and return false
			{
				logger->LogActions("Tried to add student: " + to_string(sid), "(Failed)");
				return false;
			}
		}
	}
	//if the course wasnt found then log as failed and return false
	if (courseToTake == nullptr)
	{
		logger->LogActions("Tried to add student: " + to_string(sid), "(Failed)");
		return false;
	}
	else
	{
		//create the student using the factory and the given parameters. since we have already checked that everything is valid
		Student* student = StudentCreator.CreateStudent(type, sid, courseToTake);

		//if for some reason the student can't be created, (maybe because a valid type wasnt passed in) then log as failed and return false
		if (student == nullptr)
		{
			logger->LogActions("Tried to add student: " + to_string(sid), "(Failed)");
			return false;
		}
		//make sure that the type of course assigned and the type of the student matches.
		if ((type == "UG" && courseToTake->getCourseType() == "UG") || (type == "G" && courseToTake->getCourseType() == "G"))
		{
			//push back the student and log as successful and return true
			students.push_back(student);
			//cout << "\nadded student " << sid << " students size: " << students.size() << endl;
			logger->LogActions("added student: " + to_string(sid) + " students size: " + to_string(students.size()), "(Successful)");
			return true;
		}
	}
	//if for some reason the program comes until here, then log as failed and return false.
	logger->LogActions("Tried to add student: " + to_string(sid), "(Failed)");
	return false;
}


//=============================================================================
//                               RemoveStudent
// Remove student takes in an id and remove the student from the university
//=============================================================================
bool University::RemoveStudent(int id)
{
	//loop through to find the student to remove
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i]->getID() == id) //if the student is found
		{
			students[i]->DropAllCourses(); //drop all the students courses

			//remove it from the students vector and log as successful and return true
			swap(students[i], students[students.size() - 1]); 
			students.pop_back();
			logger->LogActions("removed student: " + to_string(id) + " students size: " + to_string(students.size()), "(Successful)");
			return true;
		}
	}
	//if the student is not found then log as failed and return false
	logger->LogActions("Tried to remove student: " + to_string(id), "(Failed)");
	return false;
}

//=============================================================================
//                               AddInstructor
// given an id and a type add an instructor to the university
//=============================================================================
bool University::AddInstructor(int id, string type)
{
	//create a factory object to create the instructor
	InstructorFactory InstructorCreator;

	//check to see that the id isn't being used or is with an existing instructor
	for (int i = 0; i < instructors.size(); i++)
	{
		if (instructors[i]->getID() == id) //if it is, then log failed and return false
		{
			logger->LogActions("Tried to add instructor: " + to_string(id), "(Failed)");
			return false;
		}
	}

	//create the instructor using the factory since we have confirmed that the id is valid
	Instructor* instructor = InstructorCreator.CreateInstructor(type, id);

	//if the type given was invalid log as failed and return false
	if (instructor == nullptr)
	{
		logger->LogActions("Tried to add instructor: " + to_string(id), "(Failed)");
		return false;
	}
	//add the instructors to the university, log as success and return true
	instructors.push_back(instructor);
	logger->LogActions("added instructor: " + to_string(id) + " instructors size: " + to_string(instructors.size()), "(Successful)");
	return true;
}

//=============================================================================
//                               RemoveInstructor
// given an id, removes an instructor from the university
//=============================================================================
bool University::RemoveInstructor(int id)
{
	//loop through to find the instructor to remove
	for (int i = 0; i < instructors.size(); i++)
	{
		if (instructors[i]->getID() == id) //once its found
		{
			instructors[i]->DropAllTeachingCourses(); //drop all the courses that the instructor is teaching

			//and remove accordingly and return true
			swap(instructors[i], instructors[instructors.size() - 1]);
			instructors.pop_back();
			logger->LogActions("Removed instructor: " + to_string(id) + " instructors size: " + to_string(instructors.size()), "(Successful)");
			return true;
		}
	}
	//if the instructor wasn't found then log as failed and return false
	logger->LogActions("Tried to remove instructor: " + to_string(id), "(Failed)");
	return false;
}


//=============================================================================
//                               AssignToStudent
// given a student id and a course id, assign a course to a student
//=============================================================================
bool University::AssignToStudent(int student_id, int course_id)
{
	//find the student
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i]->getID() == student_id) //if the student is found
		{
			for (int j = 0; j < courses.size(); j++) //find the course
			{
				if (courses[j]->getCourseID() == course_id) //if the course is found
				{
					bool result = students[i]->Enroll(courses[j]); //check if you can enroll into the course
					if (result == true) //if you can then log sucess and return true
					{
						logger->LogActions("Assigned student : " + to_string(student_id) + " to course: " + to_string(course_id), "(Successful)");
						return true;
					}
					else //return false and failed
					{
						logger->LogActions("Tried to assign student: " + to_string(student_id) + " to a course", "(Failed)");
						return false;
					}
					
				}
			}
			//if we cant find the course return false and failed
			logger->LogActions("Tried to assign student: " + to_string(student_id) + " to a course", "(Failed)");
			return false;
		}
	}
	//if we cant find the student return false and failed
	logger->LogActions("Tried to assign student: " + to_string(student_id) + " to a course", "(Failed)");
	return false;
}


//=============================================================================
//                               RemoveFromStudent
// given a student id and a course id, removes a course from a student
//=============================================================================
bool University::RemoveFromStudent(int student_id, int course_id)
{
	//find the student 
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i]->getID() == student_id) //if the student is found
		{
			for (int j = 0; j < courses.size(); j++) //find the course
			{
				if (courses[j]->getCourseID() == course_id)//if the course is found
				{
					bool result = students[i]->Drop(courses[j]); //check if you can drop the course
					if (result == true) //if true then log success and return true
					{
						logger->LogActions("Removed student : " + to_string(student_id) + " from course: " + to_string(course_id), "(Successful)");
						return true;
					}
					else //if we cant drop then return false and failed
					{
						logger->LogActions("Tried to removed student: " + to_string(student_id) + " from a course", "(Failed)");
						return false;
					}

				}
			}
			//if the course isnt found then return false and failed
			logger->LogActions("Tried to assign student: " + to_string(student_id) + " from a course", "(Failed)");
			return false;
		}
	}
	//if the student isnt found return false and failed
	logger->LogActions("Tried to assign student: " + to_string(student_id) + " from a course", "(Failed)");
	return false;
}

//=============================================================================
//                               AssignToInstructor
// given a student id and a course id, assigns an instructor to a course
//=============================================================================
bool University::AssignToInstructor(int instructor_id, int course_id)
{
	//find the instructor
	for (int i = 0; i < instructors.size(); i++)
	{
		if (instructors[i]->getID() == instructor_id) //if the instructor is found
		{
			for (int j = 0; j < courses.size(); j++)//find the course
			{
				if (courses[j]->getCourseID() == course_id) //if the course is found
				{
					bool result = instructors[i]->Teach(courses[j]); //check if the instructor can teach the course
					if (result == true) //if they can then return success and true
					{
						logger->LogActions("Assigned instructor : " + to_string(instructor_id) + " to course: " + to_string(course_id), "(Successful)");
						//cout << "\ninstructor: " << instructor_id << " is now teaching course: " << course_id << endl;
						return true;
					}
					else //if they cant then return false and failed
					{
						logger->LogActions("Tried to assign instructor: " + to_string(instructor_id) + " to a course", "(Failed)");
						return false;
					}

				}
			}
			//if the course isnt found, then return false and failed
			logger->LogActions("Tried to assign instructor: " + to_string(instructor_id) + " to a course", "(Failed)");
			return false;
		}
	}
	//if the instructor isnt found, then return false and failed
	logger->LogActions("Tried to assign instructor: " + to_string(instructor_id) + " to a course", "(Failed)");
	return false;
}

//=============================================================================
//                               RemoveFromInstructor
// given a student id and a course id, removes an instructor from a course
//=============================================================================
bool University::RemoveFromInstructor(int instructor_id, int course_id)
{
	//find the instructor
	for (int i = 0; i < instructors.size(); i++)
	{
		if (instructors[i]->getID() == instructor_id)//if the instructor is found
		{
			for (int j = 0; j < courses.size(); j++)//find the course
			{
				if (courses[j]->getCourseID() == course_id)//if the course is found
				{
					bool result = instructors[i]->StopTeaching(courses[j]);//check the instructor can stop teaching
					if (result == true)//if they can then log success and return true
					{
						logger->LogActions("Removed instructor: " + to_string(instructor_id) + " from course: " + to_string(course_id), "(Successful)");
						//cout << "\ninstructor: " << instructor_id << " has stopped teaching course: " << course_id << endl;
						return true;
					}
					else //if they cant then log false and failed
					{
						logger->LogActions("Tried to remove instructor: " + to_string(instructor_id) + " to a course", "(Failed)");
						return false;
					}

				}
			}
			//if the course isnt found, then return false and failed
			logger->LogActions("Tried to remove instructor: " + to_string(instructor_id) + " to a course", "(Failed)");
			return false;
		}
	}
	//if the instructor isnt found then return false and failed
	logger->LogActions("Tried to remove instructor: " + to_string(instructor_id) + " to a course", "(Failed)");
	return false;
}

//=============================================================================
//                               PrintStudentHistory
// given a type, and a student id, prints history related to student
// Note: I assume a valid student is passed in
//=============================================================================
void University::PrintStudentHistory(int type, int sid)
{
	//if the type is 1, then print all courses a student is currently taking
	if (type == 1)
	{
	 cout << "Student " << sid << "'s Currently Enrolled Courses:" << endl;
	 for(int i = 0; i < students.size(); i++)
	 {
		 if (students[i]->getID() == sid)//find the student and print
		 {
			 students[i]->PrintCurrentlyTakingCourses();
		 }
	 }
	 //log as sucess and return
	 logger->LogActions("Printed student: " + to_string(sid) + "'s currently enrolled courses", "(Successful)");
	 return;
	}

	//if type = 2, print all courses a student has taken
	else if (type == 2)
	{
		cout << "Student " << sid << " has taken: " << endl;
		for (int i = 0; i < students.size(); i++)
		{
			if (students[i]->getID() == sid)//find the student. loop through history vector using getter and print
			{
				for (int j = 0; j < students[i]->getCourseHistory().size(); j++)
				{
					cout << "course: " << students[i]->getCourseHistory()[j]->getCourseID() << endl;
					
				}
			}
		}
		//log as success and return
		logger->LogActions("Printed student: " + to_string(sid) + "'s taken courses", "(Successful)");
		return;
	}
	else //error handling for invalid type
	{
		cout << "invalid type " << endl;
	}
}

//=============================================================================
//                               PrintCourseHistory
// given a type, and a course id, prints history related to course
// Note: I assume a valid course is passed in
//=============================================================================
void University::PrintCourseHistory(int type, int cid)
{
	//if type == 1 print all students in a course
	if (type == 1)
	{
		cout << "Students in Course: " << cid << endl;
		for (int i = 0; i < courses.size(); i++)
		{
			if (courses[i]->getCourseID() == cid)//find course an call approriate method
			{
				courses[i]->PrintAllStudents();
			}
		}
		//log as sucess and return
		logger->LogActions("Printed all students in  course: " + to_string(cid), "(Successful)");
		return;
	}
	else //error handling
	{
		cout << "invalid type " << endl;
	}

}

//=============================================================================
//                               PrintInstructorHistory
// given a type, and an id, prints history related to instructor
// Note: I assume a valid instructor is passed in
//=============================================================================
void University::PrintInstructorHistory(int type, int id)
{
	// if type = 1, print all courses an instructor is currently teaching
	if (type == 1)
	{
		cout << "Instructor " << id << " is currently teaching:" << endl;
		for (int i = 0; i < instructors.size(); i++)
		{
			if (instructors[i]->getID() == id) //find the instructor and call appropriate method
			{
				instructors[i]->PrintCurrentlyTeachingCourses();
			}
		}
		//log as success and return
		logger->LogActions("Printed instructor: " + to_string(id) + "'s currently teaching courses", "(Successful)");
		return;
	}

	//if type = 2, print all courses a instructor has taught
	else if (type == 2)
	{
		cout << "Instructor " << id << " has taught: " << endl;
		for (int i = 0; i < instructors.size(); i++)
		{
			if (instructors[i]->getID() == id)//find instructor and loop through his history vector using getter
			{
				for (int j = 0; j < instructors[i]->getCoursesTaughtHistory().size(); j++)
				{
					cout << "course: " << instructors[i]->getCoursesTaughtHistory()[j]->getCourseID() << endl;

				}
			}
		}
		//log as success and return
		logger->LogActions("Printed instructor: " + to_string(id) + "'s taught courses", "(Successful)");
		return;
	}
	else //error handling
	{
		cout << "invalid type " << endl;
	}
}

//=============================================================================
//                               PrintInstructorHistory
// given a type, Prints all courses currently being taught, 
// who their instructor is, and which students are in them to the screen
//=============================================================================
void University::PrintAllStats(int type)
{
	//if type == 1 then print to screen
	if (type == 1)
	{
		cout << "All Courses Currently being taught: " << endl;
		for (int i = 0; i < courses.size(); i++) //loop through courses vector and print for each course using appropriate method
		{

			cout << "course: " << courses[i]->getCourseID() << " course instructor : " << courses[i]->getInstructorID() << endl;
			courses[i]->PrintAllStudents();

		}
		//log as success and return
		logger->LogActions("Printed all courses currently being taught, who their instructor is, and which students are in them to the screen.", "(Successful)");
		return;
	}
	
	
	//if type = 2, then print to a file
	else if (type == 2)
	{
		//Try to clear the log before printing
		ofstream FileWriter;
		FileWriter.open("CourseStats.txt", ios_base::out);
		FileWriter << "";
		FileWriter.close();

		FileWriter.open("CourseStats.txt", ios_base::app);
		FileWriter << "All Courses Currently being taught: " << endl;
		for (int i = 0; i < courses.size(); i++)
		{

			FileWriter << "course: " << courses[i]->getCourseID() << " course instructor : " << courses[i]->getInstructorID() << endl;
			for (int j = 0; j < courses[i]->getCourse().size(); j++)
			{
				FileWriter << "student: " << courses[i]->getCourse()[j] << endl;
			}

		}
		FileWriter.close();
		logger->LogActions("Printed all courses currently being taught, who their instructor is, and which students are in them to a file.", "(Successful)");
		return;
	}
	else //error handling
	{
		cout << "invalid type " << endl;
	}
}

//=============================================================================
//                               DeleteUniversity
// Deletes the entire university
//=============================================================================
void University::DeleteUniversity()
{
	//loop through and delete courses
	for (int i = 0; i < courses.size(); i++)
	{
		RemoveCourse(courses[i]->getCourseID());
	}
	if (courses.size() == 1) //this was an error case where the for loop wasnt deleting the last item, so i just had this to check and delete
	{
		RemoveCourse(courses[0]->getCourseID());
	}

	//loop through and delete students
	for (int i = 0; i < students.size(); i++)
	{
		RemoveStudent(students[i]->getID());
	}
	if (students.size() == 1)
	{
		RemoveStudent(students[0]->getID());
	}

	//loop through and delete instructors
	for (int i = 0; i < instructors.size(); i++)
	{
		RemoveInstructor(instructors[i]->getID());
	}
	if (instructors.size() == 1)
	{
		RemoveCourse(courses[0]->getCourseID());
	}

	//make sure that everything is taken care of and clear all vectors as precaution
	courses.clear();
	students.clear();
	instructors.clear();

	//finally log as a success
	logger->LogActions("Deleted University ", "(Successful)");

}
