#pragma once

#include "Constants.h"
#include "Date.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Profile {
    string ID[MAXID]; //21125xxx
    string firstName[MAXNAME];
    string lastName[MAXNAME];
    bool gender; // male: 1, female: 0
    Date DOB; // day of birth
    string socialID[MAXID]; //xxxxxxxx

    void importFromCSV();

};