// Assignment 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "University.h"
#include "Logger.h"

int main()
{
    cout << "--------------------START-------------------------------" << endl;
    University UniversityOfWashington;
    UniversityOfWashington.AddCourse(120, "UG");
    UniversityOfWashington.AddCourse(101, "UG");
    UniversityOfWashington.AddCourse(130, "UG");
    UniversityOfWashington.AddCourse(230, "G");
    UniversityOfWashington.AddCourse(330, "G");
    UniversityOfWashington.AddCourse(201, "G");
    UniversityOfWashington.AddCourseWithPreReq(301, "G", 201);

    UniversityOfWashington.AddStudent(22214, "UG", 101);
    UniversityOfWashington.AddStudent(22216, "G", 201);
    for (int i = 0; i < 40; i++)
    {
        UniversityOfWashington.AddStudent(22217 + i, "UG", 120);
    }
    UniversityOfWashington.AssignToStudent(22216, 230);
    UniversityOfWashington.AssignToStudent(22216, 330);
    UniversityOfWashington.AssignToStudent(22216, 301);

    UniversityOfWashington.AddInstructor(10345, "F");
    UniversityOfWashington.AddInstructor(10359, "F");
    UniversityOfWashington.AddInstructor(10357, "GI");
    UniversityOfWashington.AddInstructor(10305, "F");
    UniversityOfWashington.AssignToInstructor(10345, 101);
    UniversityOfWashington.AssignToInstructor(10357, 201);
    UniversityOfWashington.AssignToInstructor(10345, 130);
    UniversityOfWashington.AssignToInstructor(10345, 301);
    UniversityOfWashington.AssignToInstructor(10359, 120);
    UniversityOfWashington.AssignToInstructor(10305, 230);
    UniversityOfWashington.AssignToInstructor(10305, 330);
 

    UniversityOfWashington.PrintAllStats(1);

    //Negatives
    UniversityOfWashington.AssignToInstructor(10345, 230);//note -1 indicates that there is no instructor for the course.
    UniversityOfWashington.AssignToInstructor(10357, 330);
    UniversityOfWashington.AssignToStudent(22214, 330); //undergraduate cannot take a graduate course
    UniversityOfWashington.RemoveFromStudent(22214, 101);//Removing works
    UniversityOfWashington.AssignToStudent(22214, 101); //studen't can't take a course, they have already taken. 
    UniversityOfWashington.AddStudent(22390, "UG", 120);//courses can't have more than 40 students at a time (students must be enrolled in one course, this student won't get created)
    UniversityOfWashington.RemoveFromStudent(22216, 230);
    UniversityOfWashington.RemoveFromStudent(22216, 301);
    UniversityOfWashington.RemoveFromInstructor(10345, 130);
    cout << endl;
    cout << "Negatives (Check Log.txt)" << endl;
    cout << endl;
    UniversityOfWashington.PrintAllStats(1);
    
    cout << endl;
    cout << "History Functions" << endl;
    cout << endl;
    UniversityOfWashington.PrintStudentHistory(1, 22216);
    cout << endl;
    UniversityOfWashington.PrintStudentHistory(2, 22216);
    cout << endl;
    UniversityOfWashington.PrintCourseHistory(1, 120);
    cout << endl;
    UniversityOfWashington.PrintInstructorHistory(1, 10345);
    cout << endl;
    UniversityOfWashington.PrintInstructorHistory(2, 10345);

    UniversityOfWashington.RemoveStudent(22216);
    UniversityOfWashington.RemoveInstructor(10345);
    UniversityOfWashington.RemoveCourse(120);
    cout << endl;
    UniversityOfWashington.PrintAllStats(1);
    UniversityOfWashington.PrintAllStats(2);

    //Finally, let's delete the university.
    UniversityOfWashington.DeleteUniversity();

    cout << "--------------------END-------------------------------" << endl;
    //Please check log.txt for all the functions status on succesful or failed. Note: I do not specify the reason for failure but I have discussed with brent and he said it's okay
    //I will make sure to clarify next time
    
    
}
