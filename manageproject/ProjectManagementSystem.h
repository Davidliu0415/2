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
   vector<Project>& getProjects(); // 返回项目列表引用

    // 管理接口
    void ProjectManage();

    void TaskManage();

    void TeamMemberManage();

    Project* getProject(const string& projectName);
    
    void loadProjectsFromCSV(const string& filename = "projects.csv");
    void saveProjectsToCSV(const string& filename = "projects.csv");

    // Task
    void loadTasksFromCSV(const string& filename = "tasks.csv", const string& projectName = "");
    void saveTasksToCSV(const string& filename = "tasks.csv");
    // TeamMember
    void loadTeamMembersFromCSV(const string& filename = "teammembers.csv", const string& projectName = "");
    void saveTeamMembersToCSV(const string& filename = "teammembers.csv");
    // Vendor
    void loadVendorsFromCSV(const string& filename = "vendors.csv");
    void saveVendorsToCSV(const string& filename = "vendors.csv");
    // Client
    void loadClientsFromCSV(const string& filename = "clients.csv");
    void saveClientsToCSV(const string& filename = "clients.csv");
    // Vendor-Project关系
    void loadVendorProjectRelations(const string& filename = "vendor_project.csv");
    void saveVendorProjectRelations(const string& filename = "vendor_project.csv");
    // Client-Project关系
    void loadClientProjectRelations(const string& filename = "client_project.csv");
    void saveClientProjectRelations(const string& filename = "client_project.csv");
};

#endif // PROJECT_MANAGEMENT_SYSTEM_H









