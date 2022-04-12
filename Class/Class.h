#include "Student.h"
#include <string.h>
#include "Constants.h"
#include "Profile.h"

struct Class {
    char name[MAXNAME];
    long long class_id;

    Class(char name[MAXNAME], long long class_id = 0);

    List<Profile> stu_list;
};

#include "Class.cpp"