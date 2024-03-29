#include "System.h"

void login()
{
    using namespace std;
    clrscr();
    std::cout << "PLEASE LOG IN USING YOUR ID AND PASSWORD.\n";
    std::cout << "Press Enter first to go back.\n\n";
    
    bool cont_out{false}; // to continue looping
    char ID[MAXID+1]; ID[0] = 0;
    char password[MAXSTR+1]; password[0] = 0;
    do {
        cout << endl;
        bool cont_in{false}; // to continue looping inside
        do {
            cout << "ID (max " << MAXID << " chars): ";
            fflush(stdin);
            cin.get(ID, MAXID+1, '\n');
            if (cin.fail()) { // nothing was inputted
                cin.clear();
                fflush(stdin);
                return;
            }
            else if (cin.get() != '\n' || !checkDigit(ID)) {
                fflush(stdin);
                cout << "Invalid ID. Please try again.\n";
                cont_in = true;
            }
            else cont_in = false;
        } while (cont_in);
        
        cont_in = false;
        do {
            cout << "Password (max " << MAXSTR << " chars): ";
            fflush(stdin);
            cin.get(password, MAXSTR+1, '\n');
            if (cin.fail() || cin.get() != '\n' || !checkAlphaDigit(password)) {
                cin.clear();
                fflush(stdin);
                cout << "Invalid password. Please try again.\n";
                cont_in = true;
            }
            else cont_in = false;
        } while (cont_in);

        if (!checkDatabase(ID, password)) {
            cout << "\nThe account's information does not exist. Please try again.\n";
            cont_out = true;
        }
        else cont_out = false;
    } while (cont_out);

    for (Node<Student>* cur = listStudents.begin(); cur; cur = cur->pNext) {
        if (strcmp(cur->data.acc.ID, ID) == 0 && strcmp(cur->data.acc.password, password) == 0) {
            cur->data.studentMenu(pOpenCourse);
            login();
            return;
        }
    }
    for (Node<Staff>* cur = listStaffs.begin(); cur; cur = cur->pNext) {
        if (strcmp(cur->data.acc.ID, ID) == 0 && strcmp(cur->data.acc.password, password) == 0) {
            cur->data.staffMenu(listStudents, pOpenCourse, pAllCourse);
            login();
            return;
        }
    }
}

bool loginScreen() {
    clrscr();
    std::cout << "0. Log in\n"
                 "1. Exit\n";
    int t{choose(0, 1)};
    if (t == 0) {
        login();
        return true;
    }
    else return false;
}

void loadAccounts()
{
    /*
    Cấu trúc quy ước của file Account database:
    N
    Accout of student 1
    Account of student 2
    ...
    Account of student N
    M
    Account of staff 1
    Account of staff 2
    ...
    Account of staff M
    */
    using namespace std;
    //std::cerr << "BEGIN TO LOAD ACCOUNTS" << std::endl;
    fstream fin("Accounts.txt", ios::in);
    if (!fin.is_open()) return;

    unsigned int N;
    fin >> N;
    //std::cerr << "N = " << N << std::endl;
    for (int i = 0; i < N; ++i) {
        Account cur;
        cur.read_data(fin);
        Student s;
        s.acc = cur;
        // std::cerr << "Student s is:" << std::endl;
        // std::cerr << s.acc.ID << std::endl << s.acc.password << std::endl << s.acc.name << std::endl << s.acc.email << std::endl << s.acc.socialID << std::endl;
        s.init_StudentInfo();
        listStudents.insert(s);
    }

    unsigned int M;
    fin >> M;
    for (int i = 0; i < M; ++i) {
        Account cur;
        cur.read_data(fin);
        Staff s;
        s.acc = cur;
        // std::cerr << "Staff s is:" << std::endl;
        // std::cerr << s.acc.ID << std::endl << s.acc.password << std::endl << s.acc.name << std::endl << s.acc.email << std::endl << s.acc.socialID << std::endl;
        listStaffs.insert(s);
    }

    fin.close();
}

void saveAccounts()
{
    // Cấu trúc quy ước được ghi trong hàm loadAccounts()
    using namespace std;
    fstream fout(ACCOUNTS_FILE, ios::out);
    if (!fout.is_open()) return;

    unsigned int N{listStudents.size()};
    fout << N << endl;
    for (Node<Student>* cur = listStudents.begin(); cur; cur = cur->pNext) {
        cur->data.acc.save_data(fout);
    }

    unsigned int M{listStaffs.size()};
    fout << M << endl;
    for (Node<Staff>* cur = listStaffs.begin(); cur; cur = cur->pNext) {
        cur->data.acc.save_data(fout);
    }
    
    fout.close();
}

int checkDatabase(const char* ID, const char* password)
{
    //std::cerr << "Checking " << ID << " and " << password << std::endl;
    for (Node<Student>* cur = listStudents.begin(); cur; cur = cur->pNext) {
        //std::cerr << "Current student " << cur->data.acc.ID << " and " << cur->data.acc.password << std::endl;
        if (strcmp(cur->data.acc.ID, ID) == 0 && strcmp(cur->data.acc.password, password) == 0)
            return 1;
    }
    for (Node<Staff>* cur = listStaffs.begin(); cur; cur = cur->pNext) {
        //std::cerr << "Current staff " << cur->data.acc.ID << " and " << cur->data.acc.password << std::endl;
        if (strcmp(cur->data.acc.ID, ID) == 0 && strcmp(cur->data.acc.password, password) == 0)
            return 2;
    }
    return 0;
}

void load_data()
{
    fstream fin(COURSES_FILE, ios::in);
    Staff dummy;
    if (fin.is_open()) {
        dummy.load_courses(fin, pAllCourse, pOpenCourse);
        fin.close();
    }

    fin.open(CLASSES_FILE, ios::in);
    if (fin.is_open()) {
        dummy.load_classes(fin, listStudents);
        fin.close();
    }
}

void save_data()
{
    fstream fout(COURSES_FILE, ios::out);
    Staff dummy;
    if (fout.is_open()) {
        dummy.save_courses(fout);
        fout.close();
    }
    else {
        std::cerr << "Cannot save the updated courses' data into " << COURSES_FILE << std::endl;
    }

    fout.open(CLASSES_FILE, ios::out);
    if (fout.is_open()) {
        dummy.save_classes(fout);
        fout.close();
    }
    else {
        std::cerr << "Cannot save the updated classes' data into " << CLASSES_FILE << std::endl;
    }
}

void load_students() {
    ifstream fin;
    fin.open("Student.txt");
    Node<Student>* p = listStudents.begin();

    while (p != NULL) {
        char inpID[MAXID+1];
        fin >> inpID;

        while (p->pNext != NULL && strcmp(p->data.acc.ID, inpID) != 0) p = p -> pNext;

        if (p != NULL && strcmp(p->data.acc.ID, inpID) == 0) 
            p->data.load_data(fin, pAllCourse);

        p = p -> pNext;
    }

    fin.close();
}

void save_students() {
    ofstream fout;
    fout.open("Student.txt");

    int cnt = 0;
    for (Node<Student>* p = listStudents.begin(); p != NULL; p = p -> pNext) 
        p->data.save_data(fout);

    fout.close();
}

