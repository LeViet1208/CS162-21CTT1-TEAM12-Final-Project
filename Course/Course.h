#pragma once

#include "..\\List\\List.h"
#include "..\\Student\\Student.h"
#include "..\\Date\\Date.h"
#include "../Profile/Profile.h"
//#include "Score.h"

#include <iostream>
#include <string>

using namespace std;

struct StudentScore{
    Profile profile;
    Score score;
};

struct Course {
 
	List <StudentScore> Student; // -> scoreboard ???
 
    Date start_date; // from Minh: có nên bỏ start_date và end_date không nhỉ vì bây giờ struct Course được bỏ vào Semester đã chứa Start_date và end_date rối ấy?
                     // from Duy: tui nghĩ không, start_date và end_date của mỗi course có thể khác nhau
                     // from Minh: à nhờ, oke ông :v
    Date end_date;
 
    char ID[MAXSTR+1]; // mã học phần
    char name[MAXSTR+1]; // tên học phần
    char lecturer[MAXSTR+1]; // tên GV
    int numCredits;
    int maxStudents{50};
	int day[7]; // "MON", "TUE", "WED", "THU", "FRI", "SAT"; 
	// S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)
    // int session; // 1 -> 4

    Course(){};

    ~Course(){
        delete this;
    };
    
    void inputCourses();
	void viewCourses();
    void updateCourse();
    void viewStudents();
    void exportStudents(); // to a CSV file
	void viewScoreboard(); //
    void addStudent();
    void isRegistrable();
};

#include "Course.cpp"
