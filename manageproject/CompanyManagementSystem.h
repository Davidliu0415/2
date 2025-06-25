#ifndef COMPANYMANAGEMENTSYSTEM_H
#define COMPANYMANAGEMENTSYSTEM_H

#include "Vendor.h"
#include "Client.h"
#include "project.h"
#include <vector>
using namespace std;

class ProjectManagementSystem; // 前向声明

class CompanyManagementSystem {
private:
    vector<Project>* projects;
    ProjectManagementSystem* pms; // 新增
public:
    CompanyManagementSystem(vector<Project>* projects, ProjectManagementSystem* pms); // 修改构造函数
    void menu();
};

#endif

