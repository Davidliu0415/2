#include "task.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

Task::Task(const string& taskID, const string& projectID, const string& name, const string& description, const string& startDate, const string& endDate, const string& status)
    : PT(name, description, startDate, endDate, status), taskID(taskID), projectID(projectID) {}

Task Task::fromCSV(const string& line) {
    stringstream ss(line);
    string taskID, projectID, name, description, startDate, endDate, status;
    getline(ss, taskID, ',');
    getline(ss, projectID, ',');
    getline(ss, name, ',');
    getline(ss, description, ',');
    getline(ss, startDate, ',');
    getline(ss, endDate, ',');
    getline(ss, status, ',');
    return Task(taskID, projectID, name, description, startDate, endDate, status);
}

string Task::toCSV() const {
    return taskID + "," + projectID + "," + getName() + "," + getDescription() + "," + getStartDate() + "," + getEndDate() + "," + getStatus();
}

// 添加任务（此处为示例，可与项目逻辑结合）
void Task::add() {
    
    // cin.ignore();  // Clear the newline character from previous cin

    cout << "Enter task name:" << endl;
    getline(cin, name);

    cout << "Enter task description:" << endl;
    getline(cin, description);

    cout << "Enter task start date (YYYY-MM-DD):" << endl;
    getline(cin, startDate);

    cout << "Enter task end date (YYYY-MM-DD):" << endl;
    getline(cin, endDate);

    cout << "Enter task status (e.g., Not Started/In Progress/Completed):" << endl;
    getline(cin, status);

    cout << "Task added successfully!" << endl;
}



// 更新任务信息
void Task::update() {
    // cin.ignore();  // Clear the newline character from previous cin

    string input;

    cout << "Enter new task name (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        name = input;
    }

    cout << "Enter new task description (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        description = input;
    }

    cout << "Enter new task start date (YYYY-MM-DD) (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        startDate = input;
    }

    cout << "Enter new task end date (YYYY-MM-DD) (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        endDate = input;
    }

    cout << "Enter new task status (e.g., Not Started/In Progress/Completed) (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        status = input;
    }

    cout << "Task information updated successfully." << endl;
}


// 移除任务（本地逻辑）
void Task::remove() {
    cout << "Task [" << name << "] marked for deletion (logical operation, local only)" << endl;
}

// 显示任务详情
void Task::display() const {
    cout << "\nTask Information:" << endl;
    cout << "Name: " << getName() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Start Date: " << getStartDate() << endl;
    cout << "End Date: " << getEndDate() << endl;
    cout << "Status: " << getStatus() << endl;

    if (!subtasks.empty()) {
        cout << "Subtask List:" << endl;
        for (const auto& sub : subtasks) {
            sub.display();
        }
    }
}

// ========== 子任务管理 ==========

void Task::addSubtask() {
    // cin.ignore();
    string name, description, startDate, endDate, status;

    cout << "Enter subtask name:" << endl;
    getline(cin, name);

    // 判断重名
    auto it = find_if(subtasks.begin(), subtasks.end(),
                      [&name](const Task& t) { return t.getName() == name; });

    if (it != subtasks.end()) {
        cout << " Subtask \"" << name << "\" already exists, addition failed.\n";
        return;
    }

    cout << "Enter subtask description:" << endl;
    getline(cin, description);

    cout << "Enter subtask start date:" << endl;
    getline(cin, startDate);

    cout << "Enter subtask end date:" << endl;
    getline(cin, endDate);

    cout << "Enter subtask status:" << endl;
    getline(cin, status);

    Task sub(name, description, startDate, endDate, status);
    subtasks.push_back(sub);
    cout << " Subtask \"" << name << "\" added successfully.\n";
}

void Task::removeSubtask() {
    cin.ignore();
    string name;
    cout << "Enter the name of the subtask to delete:" << endl;
    getline(cin, name);

    auto it = find_if(subtasks.begin(), subtasks.end(),
                      [&name](const Task& t) { return t.getName() == name; });

    if (it == subtasks.end()) {
        cout << " Subtask named \"" << name << "\" not found.\n";
        return;
    }

    subtasks.erase(it);
    cout << " Subtask \"" << name << "\" deleted.\n";
}

void Task::updateSubtask() {
    // cin.ignore();
    string name;
    cout << "Enter the name of the subtask to update:" << endl;
    getline(cin, name);

    auto it = find_if(subtasks.begin(), subtasks.end(),
                      [&name](Task& t) { return t.getName() == name; });

    if (it == subtasks.end()) {
        cout << " Subtask named \"" << name << "\" not found.\n";
        return;
    }

    string input;

    cout << "Current description: " << it->getDescription() << "\nEnter new description (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) it->setDescription(input);

    cout << "Current start date: " << it->getStartDate() << "\nEnter new start date (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) it->setStartDate(input);

    cout << "Current end date: " << it->getEndDate() << "\nEnter new end date (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) it->setEndDate(input);

    cout << "Current status: " << it->getStatus() << "\nEnter new status (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) it->setStatus(input);

    cout << " Subtask \"" << name << "\" updated.\n";
}


Task* Task::getSubtask(const string& subtaskName) {
    auto it = find_if(subtasks.begin(), subtasks.end(),
                      [&subtaskName](const Task& t) { return t.getName() == subtaskName; });

    return (it != subtasks.end()) ? &(*it) : nullptr;
}
