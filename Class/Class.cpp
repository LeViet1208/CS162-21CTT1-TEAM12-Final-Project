#include "Class.h"

using namespace std;

void Class::manageStudent(List <Student>& listStudents)
{
    clrscr();
    std::cout << "MANAGE CLASS " << ID << endl << endl;
    std::cout << "1. View a list of students.\n"
            "2. Add student.\n"
            "3. Import student from CSV file.\n"
            "4. Update student result.\n";
            "5. View scoreboard.\n";
            "6. Go back.\n\n";
    std::cout << "Your choice: ";
    int t{choose(1, 4)};
    if (t == 1) {
        viewStudentList();
        manageStudent(listStudents);
    }
    else if (t == 2) {
        addStudent(listStudents);
        manageStudent(listStudents);
    }
    else if (t == 3) {
        importStudentFile(listStudents);
        manageStudent(listStudents);
    }
    else if (t == 4) {
        updateStudentResult();
        manageStudent(listStudents);
    }
    else if (t == 5) {
        viewScoreBoard();
        manageStudent(listStudents);
    }
    else if (t == 6) {
        // lets go back
    }
    else assert(false); // just to make sure this case cannot happen
}

void Class::viewStudentList()
{
    clrscr();
    std::cout << "STUDENT LIST " << endl << endl;

    int N{1};
    for (Node <Student*> *i; i; i = i -> pNext)
    {
        std::cout << N++ << ". " << i->data->acc.name << "\n";
    }

    system("pause");
}

void Class::inputClass()
{
    cout << "Enter class name: ";
    cin.get(ID, MAXSTR+1, '\n');
}

bool Class::addStudent(List<Student>& listStudents) {
    clrscr();
    std::cout << "ADD A NEW STUDENT TO THIS CLASS\n\n";
    
    char inpID[MAXID+1];
    cout << "Please enter Student ID: ";
    cin >> inpID;

    for (Node<Student>* p = listStudents.begin(); p; p = p -> pNext) 
        if (strcmp(inpID, (p->data).acc.ID)) {
            studentsList.insert(&(p->data));
            return true;
        }
    
    cout << "Invalid Student ID! Please check it again";
    return false;
}

void Class::importStudentFile(List <Student>& listStudents) {
    ifstream fin;
    fin.open("input.csv", ios::in);

    if (!fin.is_open()) {
        cout << "Invalid File!";
        return;
    }

    vector<string> row;
    string inpID;

    if (!fin.eof()) {
        do {
            getline(fin, inpID);

            for (Node<Student>* p = listStudents.begin(); p; p = p -> pNext) {
                bool sameID = true;
                for (int j = 0; j < inpID.length(); ++j)
                    if (inpID[j] != (p->data).acc.ID[j]) sameID = false;
                if (sameID) {
                    studentsList.insert(&(p->data));
                    break;
                }
            }
            
        } while (!fin.eof());
    }
    // return res;
}

void Class::viewScoreBoard()
{
    clrscr();
    std::cout << "SCORE BOARD OF CLASS " << ID << endl << endl;

    cout << "No\tStudentID\tStudentName\tCourse\tmidTerm\tFinal\n";
    int N{0};
    for (Node <Student*> *curStudent = studentsList.begin(); curStudent; curStudent = curStudent -> pNext)
    {
        for (Node <CourseScore> *curCourse = curStudent->data->CoursesList.begin(); curCourse; curCourse = curCourse -> pNext)
        {
            cout << ++N << "\t"
                << curStudent->data->acc.ID << "\t"
                << curStudent->data->acc.name << "\t"
                << curCourse->data.pCourse->info.name << "\t"
                << curCourse->data.pScore->midTerm << "\t"
                << curCourse->data.pScore->Final << "\n";
        }
    }

    system("pause");
}

void Class::updateStudentResult()
{
    clrscr();
    std::cout << "STUDENT LIST " << endl << endl;

    int N{0};
    for (Node <Student*> *i; i; i = i -> pNext)
    {
        std::cout << ++N << ". " << i->data->acc.name << "\n";
    }

    cout << "Enter student you want to update result (1 -> " << N << "): ";
    int t = choose(1, N);
    
    studentsList.get(t-1)->updateResult();
}