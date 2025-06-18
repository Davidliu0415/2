#ifndef PROJECT_H
#define PROJECT_H

#include "pt.h"
#include "Task.h"
#include "TeamMenber.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;

class Project : public PT {
private:
    vector<Task> tasks;
    vector<TeamMember> teamMembers;

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
    // bool addTask(const Task& task);
    // bool removeTask(const string& taskName);
    // bool updateTask(const string& taskName, const Task& newTask);
    // Task* getTask(const string& taskName);

    // // Team member management
    // bool addTeamMember(const TeamMember& member);
    // bool removeTeamMember(const string& memberName);
    // bool updateTeamMember(const string& memberName, const TeamMember& newMember);
    // TeamMember* getTeamMember(const string& memberName);

    // // Static methods
    // static Project* getProject(const string& projectName);
    // static vector<Project>& getAllProjects();
    // static bool saveToFile(const string& filename);
    // static bool loadFromFile(const string& filename);
};

#endif // PROJECT_H
