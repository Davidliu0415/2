#ifndef PROJECT_H
#define PROJECT_H

#include "pt.h"
#include "Task.h"
#include "TeamMenber.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Vendor; // 前向声明
class Client; // 前向声明

class Project : public PT {
private:
    vector<Task> tasks;
    vector<TeamMember> teamMembers;
    vector<Vendor*> vendors;
    vector<Client*> clients;

public:
    Project(const string& name = "",
            const string& description = "",
            const string& startDate = "",
            const string& endDate = "",
            const string& status = "Not Started");

    // CRUD operations
    void add() ;
    void update() ;
    void remove() ;
    void display() const override;

    // // Task management
    bool addTask(const Task& task);
    bool removeTask(const string& taskName);
    bool updateTask(const string& taskName, const Task& newTask);
    Task* getTask(const string& taskName);

    // Team member management
    bool addTeamMember(const TeamMember& member);
    bool removeTeamMember(const string& memberName);
    bool updateTeamMember(const string& memberName, const TeamMember& newMember);
    TeamMember* getTeamMember(const string& memberName);

    // 在 public 中添加：
    vector<Task>& getTasks(); // 返回任务列表引用
    vector<TeamMember>& getTeamMembers(); // 返回成员列表引用
    
    // Const versions for const objects
    const vector<Task>& getTasks() const; // 返回任务列表常量引用
    const vector<TeamMember>& getTeamMembers() const; // 返回成员列表常量引用

    // Vendor management
    void addVendor(Vendor* v);
    void removeVendor(Vendor* v);
    vector<Vendor*>& getVendors();
    const vector<Vendor*>& getVendors() const { return vendors; }

    // Client management
    void addClient(Client* c);
    void removeClient(Client* c);
    vector<Client*>& getClients();
    const vector<Client*>& getClients() const { return clients; }

    // // Static methods
    // static Project* getProject(const string& projectName);
    // static vector<Project>& getAllProjects();
    // static bool saveToFile(const string& filename);
    // static bool loadFromFile(const string& filename);

    // 静态方法：保存所有项目到CSV
    static bool saveToCSV(const std::vector<Project>& projects, const std::string& filename);

    // 静态方法：从CSV加载所有项目
    static bool loadFromCSV(std::vector<Project>& projects, const std::string& filename);

    // 保存所有项目及其任务、成员、供应商、客户到project.csv
    static bool saveAllToCSV(const std::vector<Project>& projects, const std::string& filename);
    // 从project.csv加载所有项目及其任务、成员、供应商、客户
    static bool loadAllFromCSV(std::vector<Project>& projects, const std::string& filename);
};

#endif // PROJECT_H
