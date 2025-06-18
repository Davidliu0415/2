#include "project.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>


// 构造函数实现
Project::Project(const string& name, const string& description, 
                const string& startDate, const string& endDate, 
                const string& status)
    : PT(name, description, startDate, endDate, status) {}



void Project::display() const {
    cout << "\n项目信息：" << endl;
    cout << "名称: " << getName() << endl;
    cout << "描述: " << getDescription() << endl;
    cout << "开始日期: " << getStartDate() << endl;
    cout << "结束日期: " << getEndDate() << endl;
    cout << "状态: " << getStatus() << endl;
    
    cout << "\n任务列表：" << endl;
    for (const auto& task : tasks) {
        task.display();
    }
    
    cout << "\n团队成员：" << endl;
    for (const auto& member : teamMembers) {
        member.display();
    }
}

//add函数
void Project::add() {
    cin.ignore();  // 清空前一次 cin 后残留的换行符

    cout << "请输入项目名称：" << endl;
    getline(cin, name);

    cout << "请输入项目描述：" << endl;
    getline(cin, description);

    cout << "请输入项目开始日期 (YYYY-MM-DD)：" << endl;
    getline(cin, startDate);

    cout << "请输入项目结束日期 (YYYY-MM-DD)：" << endl;
    getline(cin, endDate);

    cout << "请输入项目状态（如 Not Started/In Progress/Completed）：" << endl;
    getline(cin, status);

    cout << "项目添加成功！" << endl;
}

//delete函数,删除这个project
// void Project::remove() {
//     cout << "请输入项目名称：" << endl;
//     cin >> name;
//     //删除这个project
//     projects.erase(remove_if(projects.begin(), projects.end(), [this](const Project& p) { return p.getName() == name; }), projects.end());
//     }

void Project::update() {
    cin.ignore();  // 清除之前 cin 留下的回车符

    string input;

    cout << "请输入新项目名称（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        name = input;
    }

    cout << "请输入新项目描述（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        description = input;
    }

    cout << "请输入新项目开始日期 (YYYY-MM-DD)（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        startDate = input;
    }

    cout << "请输入新项目结束日期 (YYYY-MM-DD)（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        endDate = input;
    }

    cout << "请输入新项目状态（如 Not Started/In Progress/Completed）（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        status = input;
    }

    cout << " 项目信息已更新完成。" << endl;
}




// // 任务管理实现
// bool Project::addTask(const Task& task) {
//     if (getTask(task.getName()) != nullptr) {
//         return false;
//     }
//     tasks.push_back(task);
//     return true;
// }

// bool Project::removeTask(const string& taskName) {
//     auto it = find_if(tasks.begin(), tasks.end(),
//         [&taskName](const Task& t) { return t.getName() == taskName; });
    
//     if (it != tasks.end()) {
//         tasks.erase(it);
//         return true;
//     }
//     return false;
// }

// bool Project::updateTask(const string& taskName, const Task& newTask) {
//     auto it = find_if(tasks.begin(), tasks.end(),
//         [&taskName](const Task& t) { return t.getName() == taskName; });
    
//     if (it != tasks.end()) {
//         *it = newTask;
//         return true;
//     }
//     return false;
// }

// Task* Project::getTask(const string& taskName) {
//     auto it = find_if(tasks.begin(), tasks.end(),
//         [&taskName](const Task& t) { return t.getName() == taskName; });
    
//     return it != tasks.end() ? &(*it) : nullptr;
// }

// // 团队成员管理实现
// bool Project::addTeamMember(const TeamMember& member) {
//     if (getTeamMember(member.getName()) != nullptr) {
//         return false;
//     }
//     teamMembers.push_back(member);
//     return true;
// }

// bool Project::removeTeamMember(const string& memberName) {
//     auto it = find_if(teamMembers.begin(), teamMembers.end(),
//         [&memberName](const TeamMember& m) { return m.getName() == memberName; });
    
//     if (it != teamMembers.end()) {
//         teamMembers.erase(it);
//         return true;
//     }
//     return false;
// }

// bool Project::updateTeamMember(const string& memberName, const TeamMember& newMember) {
//     auto it = find_if(teamMembers.begin(), teamMembers.end(),
//         [&memberName](const TeamMember& m) { return m.getName() == memberName; });
    
//     if (it != teamMembers.end()) {
//         *it = newMember;
//         return true;
//     }
//     return false;
// }

// TeamMember* Project::getTeamMember(const string& memberName) {
//     auto it = find_if(teamMembers.begin(), teamMembers.end(),
//         [&memberName](const TeamMember& m) { return m.getName() == memberName; });
    
//     return it != teamMembers.end() ? &(*it) : nullptr;
// }
// // 静态方法实现
// Project* Project::getProject(const string& projectName) {
//     auto it = find_if(projects.begin(), projects.end(),
//         [&projectName](const Project& p) { return p.getName() == projectName; });
    
//     return it != projects.end() ? &(*it) : nullptr;
// }

// vector<Project>& Project::getAllProjects() {
//     return projects;
// }

// bool Project::saveToFile(const string& filename) {
//     ofstream file(filename);
//     if (!file.is_open()) {
//         return false;
//     }

//     for (const auto& project : projects) {
//         file << project.getName() << ","
//              << project.getDescription() << ","
//              << project.getStartDate() << ","
//              << project.getEndDate() << ","
//              << project.getStatus() << endl;
//     }

//     file.close();
//     return true;
// }

// bool Project::loadFromFile(const string& filename) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         return false;
//     }

//     projects.clear();
//     string line;
//     while (getline(file, line)) {
//         stringstream ss(line);
//         string name, description, startDate, endDate, status;
        
//         getline(ss, name, ',');
//         getline(ss, description, ',');
//         getline(ss, startDate, ',');
//         getline(ss, endDate, ',');
//         getline(ss, status, ',');

//         Project project(name, description, startDate, endDate, status);
//         projects.push_back(project);
//     }

//     file.close();
//     return true;
//}

