#include "Schoolyear.h"
#include <cassert>

void Schoolyear::createSemester() {
    Semester semester;
    int choose;
    if (listSemesters.size() > 3) {
        cout << "You can only create 3 semesters." << endl;
        return;
    }
    cout << "Do you really want to create semester " << listSemesters.size()+1 <<"? (0 for No and 1 for Yes): ";
    cin >> choose;
    if (choose == 0){
        return;
    }
    Semester semester;
    // semester.created=true;
    semester.index = listSemesters.size();
    listSemesters.insert(semester);
    cout << "What is the start date of this semester (example: 2020-01-01)?\n";
    semester.start_date.enter_date();

    cout << "What is the end date of this semester (example: 2020-03-31)?\n";
    semester.end_date.enter_date();
}

void Schoolyear::manageSemesters()
{
    clrscr();
    int N{0};
    for (Node<Semester>* cur = listSemesters.begin(); cur; cur = cur->pNext) {
        std::cout << N++ << ". View semester " << N << endl;
    }
    std::cout << N++ << ". Create a new semester\n";
    std::cout << N++ << ". Go back\n";
    int t{choose(0, N - 1)};
    if (t < N - 2) {
        listSemesters.get(t).manageCourses();
        manageSemesters();
    }
    else if (t == N - 2) {
        createSemester();
        manageSemesters();
    }
    else if (t == N - 1) {
        // lets go back
    }
    else assert(false); // just to make sure this case cannot happen
}