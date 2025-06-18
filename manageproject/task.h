#ifndef TASK_H
#define TASK_H

#include "pt.h"
#include <vector>
#include <string>

using namespace std;

// 前向声明，避免循环依赖

class Task : public PT {
private:
    vector<Task> subtasks;
    // Project* parentProject = nullptr;
    // Task* parentTask = nullptr;

public:
    Task(const string& name = "",
         const string& description = "",
         const string& startDate = "",
         const string& endDate = "",
         const string& status = "Not Started");

    // CRUD operations
    void add() ;
    void update() ;
    void remove() ;
    void display() const override;

    // Subtask management
    void addSubtask();
    void removeSubtask();
    void updateSubtask();
    Task* getSubtask(const string& subtaskName);

    // // Project association
    // void setParentProject(Project* project);
    // Project* getParentProject() const;

    // // Parent task association
    // void setParentTask(Task* task);
    // Task* getParentTask() const;

    // Static methods
    // static Task* getTask(const string& taskName);
    // static vector<Task>& getAllTasks();
    // static bool saveToFile(const string& filename);
    // static bool loadFromFile(const string& filename);
};

#endif // TASK_H
