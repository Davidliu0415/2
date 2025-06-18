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
    // 在 public 中添加：
    vector<Task>& getTasks(); // 返回任务列表引用
   vector<TeamMember>& getTeamMembers(); // 返回成员列表引用


    // 管理接口
    void ProjectManage();

    void TaskManage();

    void TeamMemberManage();

    Project* getProject(const string& projectName);
    
};

#endif // PROJECT_MANAGEMENT_SYSTEM_H









