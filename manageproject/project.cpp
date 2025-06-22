#include "project.h"
#include "Vendor.h"
#include "Client.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>


// Constructor implementation
Project::Project(const string& name, const string& description, 
                const string& startDate, const string& endDate, 
                const string& status)
    : PT(name, description, startDate, endDate, status) {}



void Project::display() const {
    cout << "\nProject Information:" << endl;
    cout << "Name: " << getName() << endl;
    cout << "Description: " << getDescription() << endl;
    cout << "Start Date: " << getStartDate() << endl;
    cout << "End Date: " << getEndDate() << endl;
    cout << "Status: " << getStatus() << endl;
    
    cout << "\nTask List:" << endl;
    for (const auto& task : tasks) {
        task.display();
    }
    
    cout << "\nTeam Members:" << endl;
    for (const auto& member : teamMembers) {
        member.display();
    }

    cout << "\nVendors: ";
    try {
        if (vendors.empty()) {
            cout << "None";
        } else {
            for (const auto* v : vendors) {
                if (v && !v->getCompanyName().empty()) {
                    cout << v->getCompanyName() << " ";
                }
            }
        }
    } catch (const std::exception& e) {
        cout << "Error displaying vendors: " << e.what();
    } catch (...) {
        cout << "Unknown error displaying vendors";
    }
    cout << endl;
    
    cout << "Clients: ";
    try {
        if (clients.empty()) {
            cout << "None";
        } else {
            for (const auto* c : clients) {
                if (c && !c->getCompanyName().empty()) {
                    cout << c->getCompanyName() << " ";
                }
            }
        }
    } catch (const std::exception& e) {
        cout << "Error displaying clients: " << e.what();
    } catch (...) {
        cout << "Unknown error displaying clients";
    }
    cout << endl;
}

//add function
void Project::add() {
    cin.ignore();  // Clear the newline character from previous cin

    cout << "Enter project name:" << endl;
    getline(cin, name);

    cout << "Enter project description:" << endl;
    getline(cin, description);

    cout << "Enter project start date (YYYY-MM-DD):" << endl;
    getline(cin, startDate);

    cout << "Enter project end date (YYYY-MM-DD):" << endl;
    getline(cin, endDate);

    cout << "Enter project status (e.g., Not Started/In Progress/Completed):" << endl;
    getline(cin, status);

    ;
}

//delete function, delete this project
// void Project::remove() {
//     cout << "请输入项目名称：" << endl;
//     cin >> name;
//     //删除这个project
//     projects.erase(remove_if(projects.begin(), projects.end(), [this](const Project& p) { return p.getName() == name; }), projects.end());
//     }

void Project::update() {
    cin.ignore();  // Clear the newline character from previous cin

    string input;

    cout << "Enter new project name (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        name = input;
    }

    cout << "Enter new project description (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        description = input;
    }

    cout << "Enter new project start date (YYYY-MM-DD) (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        startDate = input;
    }

    cout << "Enter new project end date (YYYY-MM-DD) (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        endDate = input;
    }

    cout << "Enter new project status (e.g., Not Started/In Progress/Completed) (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        status = input;
    }

    cout << "Project information updated successfully." << endl;
}




// Task management implementation
bool Project::addTask(const Task& task) {
    if (getTask(task.getName()) != nullptr) {
        return false;
    }
    tasks.push_back(task);
    return true;
}

bool Project::removeTask(const string& taskName) {
    auto it = find_if(tasks.begin(), tasks.end(),
        [&taskName](const Task& t) { return t.getName() == taskName; });
    
    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }
    return false;
}

bool Project::updateTask(const string& taskName, const Task& newTask) {
    auto it = find_if(tasks.begin(), tasks.end(),
        [&taskName](const Task& t) { return t.getName() == taskName; });
    
    if (it != tasks.end()) {
        *it = newTask;
        return true;
    }
    return false;
}

Task* Project::getTask(const string& taskName) {
    auto it = find_if(tasks.begin(), tasks.end(),
        [&taskName](const Task& t) { return t.getName() == taskName; });
    
    return it != tasks.end() ? &(*it) : nullptr;
}

// Team member management implementation
bool Project::addTeamMember(const TeamMember& member) {
    if (getTeamMember(member.getName()) != nullptr) {
        return false;
    }
    teamMembers.push_back(member);
    return true;
}

TeamMember* Project::getTeamMember(const string& memberName) {
    auto it = find_if(teamMembers.begin(), teamMembers.end(),
        [&memberName](const TeamMember& m) { return m.getName() == memberName; });
    
    return it != teamMembers.end() ? &(*it) : nullptr;
}

bool Project::removeTeamMember(const string& memberName) {
    auto it = find_if(teamMembers.begin(), teamMembers.end(),
        [&memberName](const TeamMember& m) { return m.getName() == memberName; });
    
    if (it != teamMembers.end()) {
        teamMembers.erase(it);
        return true;
    }
    return false;
}

// Static method implementation
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

vector<Task>& Project::getTasks() {
    return tasks;
}
vector<TeamMember>& Project::getTeamMembers() {
    return teamMembers;
}

void Project::addVendor(Vendor* v) {
    if (std::find(vendors.begin(), vendors.end(), v) == vendors.end())
        vendors.push_back(v);
}
void Project::removeVendor(Vendor* v) {
    vendors.erase(std::remove(vendors.begin(), vendors.end(), v), vendors.end());
}
std::vector<Vendor*>& Project::getVendors() { return vendors; }

void Project::addClient(Client* c) {
    if (std::find(clients.begin(), clients.end(), c) == clients.end())
        clients.push_back(c);
}
void Project::removeClient(Client* c) {
    clients.erase(std::remove(clients.begin(), clients.end(), c), clients.end());
}
std::vector<Client*>& Project::getClients() { return clients; }
