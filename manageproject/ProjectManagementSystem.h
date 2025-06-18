#ifndef PROJECTMANAGEMENTSYSTEM_H
#define PROJECTMANAGEMENTSYSTEM_H

#include<iostream>
#include<string>
#include<vector>
#include"project.h"
#include"Task.h"
#include"TeamMenber.h"

using namespace std;

class ProjectManagementSystem {
private:
    vector<Project> projects;

public:
    ProjectManagementSystem();
    ~ProjectManagementSystem();
    // Add in public:
    vector<Task>& getTasks(); // Return task list reference
    vector<TeamMember>& getTeamMembers(); // Return team member list reference

    // Management interfaces
    void ProjectManage();
    void TaskManage();
    void TeamMemberManage();
    Project* getProject(const string& projectName);
};

#endif // PROJECT_MANAGEMENT_SYSTEM_H









