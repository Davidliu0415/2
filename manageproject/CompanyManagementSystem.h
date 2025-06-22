#ifndef COMPANYMANAGEMENTSYSTEM_H
#define COMPANYMANAGEMENTSYSTEM_H

#include "Vendor.h"
#include "Client.h"
#include "project.h"
#include <vector>
using namespace std;

class CompanyManagementSystem {
private:
    vector<Project>* projects;
public:
    CompanyManagementSystem(vector<Project>* projects);
    void menu();
};

#endif
