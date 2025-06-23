#include "ProjectManagementSystem.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Vendor.h"
#include "Client.h"
#include "company.h"

ProjectManagementSystem::ProjectManagementSystem() {
    cout << "Project Management System Started\n";
    loadProjectsFromCSV();
}

ProjectManagementSystem::~ProjectManagementSystem() {
    cout << "Project Management System Closed\n";
}

// ==================== Find Project ====================
Project* ProjectManagementSystem::getProject(const string& projectName) {
    auto it = find_if(projects.begin(), projects.end(),
                      [&projectName](const Project& p) {
                          return p.getName() == projectName;
                      });

    return (it != projects.end()) ? &(*it) : nullptr;
}

// ==================== Project Management ====================
void ProjectManagementSystem::loadProjectsFromCSV(const string& filename) {
    projects.clear();
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, desc, start, end, status, vstr, cstr, tmstr, tstr;
        getline(ss, name, ',');
        getline(ss, desc, ',');
        getline(ss, start, ',');
        getline(ss, end, ',');
        getline(ss, status, ',');
        getline(ss, vstr, ',');
        getline(ss, cstr, ',');
        getline(ss, tmstr, ',');
        getline(ss, tstr, ',');
        Project p(name, desc, start, end, status);
        // 解析Vendor
        stringstream vss(vstr);
        string vname;
        while (getline(vss, vname, ';')) {
            if (!vname.empty()) {
                Vendor* v = Vendor::getVendor(vname);
                if (v) p.addVendor(v);
            }
        }
        // 解析Client
        stringstream css(cstr);
        string cname;
        while (getline(css, cname, ';')) {
            if (!cname.empty()) {
                Client* c = Client::getClient(cname);
                if (c) p.addClient(c);
            }
        }
        // 解析TeamMember
        stringstream tmss(tmstr);
        string tmname;
        while (getline(tmss, tmname, ';')) {
            if (!tmname.empty()) {
                // 这里只能恢复名字，详细信息需在teammembers.csv中查找
                p.addTeamMember(TeamMember(tmname));
            }
        }
        // 解析Task
        stringstream tss(tstr);
        string tname;
        while (getline(tss, tname, ';')) {
            if (!tname.empty()) {
                // 这里只能恢复名字，详细信息需在tasks.csv中查找
                p.addTask(Task(tname));
            }
        }
        projects.push_back(p);
    }
    file.close();
}

void ProjectManagementSystem::saveProjectsToCSV(const string& filename) {
    ofstream file(filename, ios::trunc);
    for (const auto& p : projects) {
        file << p.getName() << ","
             << p.getDescription() << ","
             << p.getStartDate() << ","
             << p.getEndDate() << ","
             << p.getStatus() << ",";
        // Vendors
        for (size_t i = 0; i < p.getVendors().size(); ++i) {
            file << p.getVendors()[i]->getCompanyName();
            if (i + 1 < p.getVendors().size()) file << ";";
        }
        file << ",";
        // Clients
        for (size_t i = 0; i < p.getClients().size(); ++i) {
            file << p.getClients()[i]->getCompanyName();
            if (i + 1 < p.getClients().size()) file << ";";
        }
        file << ",";
        // TeamMembers
        for (size_t i = 0; i < p.getTeamMembers().size(); ++i) {
            file << p.getTeamMembers()[i].getName();
            if (i + 1 < p.getTeamMembers().size()) file << ";";
        }
        file << ",";
        // Tasks
        for (size_t i = 0; i < p.getTasks().size(); ++i) {
            file << p.getTasks()[i].getName();
            if (i + 1 < p.getTasks().size()) file << ";";
        }
        file << endl;
    }
    file.close();
}

void ProjectManagementSystem::ProjectManage() {
    loadProjectsFromCSV(); // 保证每次进入菜单都同步
    while (true) {
        cout << "\n=== Project Management ===" << endl;
        cout << "1. Add Project" << endl;
        cout << "2. Modify Project" << endl;
        cout << "3. Delete Project" << endl;
        cout << "4. Display All Projects" << endl;
        cout << "0. Return to Main Menu" << endl;
        cout << "Please select an option: ";
        int choice;
        cin >> choice;
        if (choice == 0) break;
        string name;
        Project temp;
        switch (choice) {
            case 1:
                temp.add();
                if (!getProject(temp.getName())) {
                    projects.push_back(temp);
                    saveProjectsToCSV();
                    cout << " Project added successfully!" << endl;
                } else {
                    cout << " Project with same name already exists!" << endl;
                }
                break;
            case 2: {
                cout << "Enter project name to modify: ";
                cin.ignore();
                string name;
                getline(cin, name);
                bool found = false;
                for (auto& project : projects) {
                    if (project.getName() == name) {
                        project.update();
                        found = true;
                        saveProjectsToCSV();
                    }
                }
                if (!found) {
                    cout << " Project \"" << name << "\" not found!" << endl;
                }
                break;
            }
            case 3: {
                string name;
                cout << "Enter project name to delete: ";
                cin.ignore();
                getline(cin, name);
                bool deleted = false;
                for (auto it = projects.begin(); it != projects.end(); ++it) {
                    if (it->getName() == name) {
                        projects.erase(it);
                        saveProjectsToCSV();
                        cout << " Project \"" << name << "\" deleted successfully.\n";
                        deleted = true;
                        break;
                    }
                }
                if (!deleted) {
                    cout << " Project \"" << name << "\" not found.\n";
                }
                break;
            }
            case 4:
                for (const auto& p : projects) {
                    p.display();
                    cout << "----------------------" << endl;
                }
                break;
            default:
                cout << " Invalid option!" << endl;
        }
    }
}

// ==================== Task Management ====================
void ProjectManagementSystem::loadTasksFromCSV(const string& filename, const string& projectName) {
    if (projectName.empty()) return;
    Project* project = getProject(projectName);
    if (!project) return;
    project->getTasks().clear();
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string pName, name, description, startDate, endDate, status;
        getline(ss, pName, ',');
        getline(ss, name, ',');
        getline(ss, description, ',');
        getline(ss, startDate, ',');
        getline(ss, endDate, ',');
        getline(ss, status, ',');
        if (pName == projectName && !name.empty()) {
            project->addTask(Task(name, description, startDate, endDate, status));
        }
    }
    file.close();
}

void ProjectManagementSystem::saveTasksToCSV(const string& filename) {
    ofstream file(filename, ios::trunc);
    for (const auto& project : projects) {
        for (const auto& t : project.getTasks()) {
            file << project.getName() << ","
                 << t.getName() << ","
                 << t.getDescription() << ","
                 << t.getStartDate() << ","
                 << t.getEndDate() << ","
                 << t.getStatus() << endl;
        }
    }
    file.close();
}

void ProjectManagementSystem::TaskManage() {
    cin.ignore();
    cout << "Enter project name: ";
    string pname;
    getline(cin, pname);
    Project* project = getProject(pname);
    if (!project) {
        cout << " Project does not exist, cannot manage tasks." << endl;
        return;
    }
    loadTasksFromCSV("tasks.csv", pname);
    while (true) {
        cout << "\n=== Task Management (Project: " << pname << ") ===" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Modify Task" << endl;
        cout << "3. Delete Task" << endl;
        cout << "4. Display Task List" << endl;
        cout << "5. Manage Subtasks" << endl;
        cout << "0. Return to Previous Menu" << endl;
        cout << "Please select an option: ";
        int choice;
        cin >> choice;
        cin.ignore();
        string tname;
        Task temp;
        switch (choice) {
            case 0: return;
            case 1:
                temp.add();
                if (!project->getTask(temp.getName())) {
                    project->addTask(temp);
                    saveTasksToCSV();
                    saveProjectsToCSV();
                } else {
                    cout << " Task with same name already exists." << endl;
                }
                break;
            case 2:
                cout << "Enter task name to modify: ";
                getline(cin, tname);
                if (Task* t = project->getTask(tname)) {
                    t->update();
                    saveTasksToCSV();
                    saveProjectsToCSV();
                } else {
                    cout << " Task not found." << endl;
                }
                break;
            case 3:
                cout << "Enter task name to delete: ";
                getline(cin, tname);
                if (project->removeTask(tname)) {
                    saveTasksToCSV();
                    saveProjectsToCSV();
                } else {
                    cout << " Delete failed, task does not exist." << endl;
                }
                break;
            case 4:
                for (const Task& t : project->getTasks()) {
                    t.display();
                    cout << "----------------" << endl;
                }
                break;
            case 5: {
                cout << "Please enter the task name to manage its subtasks: ";
                getline(cin, tname);
                Task* t = project->getTask(tname);
                if (!t) {
                    cout << "Task not found!" << endl;
                    break;
                }
                bool subtask_menu = true;
                while (subtask_menu) {
                    cout << "\n=== Subtask Management (Task: " << t->getName() << ") ===" << endl;
                    cout << "1. Add Subtask" << endl;
                    cout << "2. Edit Subtask" << endl;
                    cout << "3. Delete Subtask" << endl;
                    cout << "4. Show All Subtasks" << endl;
                    cout << "0. Return to Previous Menu" << endl;
                    cout << "Please select: ";
                    int subchoice;
                    cin >> subchoice;
                    cin.ignore();
                    switch (subchoice) {
                        case 0: subtask_menu = false; break;
                        case 1: t->addSubtask(); saveProjectsToCSV(); break;
                        case 2: t->updateSubtask(); saveProjectsToCSV(); break;
                        case 3: t->removeSubtask(); saveProjectsToCSV(); break;
                        case 4: t->display(); break;
                        default: cout << "Invalid option" << endl;
                    }
                }
                break;
            }
            default:
                cout << " Invalid option" << endl;
        }
    }
}

// ==================== Team Member Management ====================
void ProjectManagementSystem::loadTeamMembersFromCSV(const string& filename, const string& projectName) {
    if (projectName.empty()) return;
    Project* project = getProject(projectName);
    if (!project) return;
    project->getTeamMembers().clear();
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string pName, name, role, contactInfo;
        getline(ss, pName, ',');
        getline(ss, name, ',');
        getline(ss, role, ',');
        getline(ss, contactInfo, ',');
        if (pName == projectName && !name.empty()) {
            project->addTeamMember(TeamMember(name, role, contactInfo));
        }
    }
    file.close();
}

void ProjectManagementSystem::saveTeamMembersToCSV(const string& filename) {
    ofstream file(filename, ios::trunc);
    for (const auto& project : projects) {
        for (const auto& m : project.getTeamMembers()) {
            file << project.getName() << ","
                 << m.getName() << ","
                 << m.getRole() << ","
                 << m.getContactInfo() << endl;
        }
    }
    file.close();
}

void ProjectManagementSystem::TeamMemberManage() {
    cin.ignore();
    cout << "Enter project name: ";
    string pname;
    getline(cin, pname);
    Project* project = getProject(pname);
    if (!project) {
        cout << " Project does not exist, cannot manage team members." << endl;
        return;
    }
    loadTeamMembersFromCSV("teammembers.csv", pname);
    while (true) {
        cout << "\n=== Team Member Management (Project: " << pname << ") ===" << endl;
        cout << "1. Add Member" << endl;
        cout << "2. Modify Member" << endl;
        cout << "3. Delete Member" << endl;
        cout << "4. Display Member List" << endl;
        cout << "0. Return to Previous Menu" << endl;
        cout << "Please select an option: ";
        int choice;
        cin >> choice;
        cin.ignore();
        string mname;
        TeamMember temp;
        switch (choice) {
            case 0: return;
            case 1:
                temp.add();
                if (!project->getTeamMember(temp.getName())) {
                    project->addTeamMember(temp);
                    saveTeamMembersToCSV();
                    saveProjectsToCSV();
                } else {
                    cout << " Member with same name already exists." << endl;
                }
                break;
            case 2:
                cout << "Enter member name to modify: ";
                getline(cin, mname);
                if (TeamMember* m = project->getTeamMember(mname)) {
                    m->update();
                    saveTeamMembersToCSV();
                    saveProjectsToCSV();
                } else {
                    cout << " Member not found." << endl;
                }
                break;
            case 3:
                cout << "Enter member name to delete: ";
                getline(cin, mname);
                if (project->removeTeamMember(mname)) {
                    saveTeamMembersToCSV();
                    saveProjectsToCSV();
                } else {
                    cout << " Delete failed, member does not exist." << endl;
                }
                break;
            case 4:
                for (const TeamMember& m : project->getTeamMembers()) {
                    m.display();
                    cout << "----------------" << endl;
                }
                break;
            default:
                cout << " Invalid option" << endl;
        }
    }
}

vector<Project>& ProjectManagementSystem::getProjects() {
    return projects;
}

// ==================== Vendor CSV ====================
void ProjectManagementSystem::loadVendorsFromCSV(const string& filename) {
    Vendor::getAllVendors().clear();
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, type, contact;
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, contact, ',');
        if (!name.empty()) {
            Vendor::getAllVendors().emplace_back(name, type, contact);
        }
    }
    file.close();
}

void ProjectManagementSystem::saveVendorsToCSV(const string& filename) {
    ofstream file(filename, ios::trunc);
    for (const auto& v : Vendor::getAllVendors()) {
        string contact = "";
        auto contacts = v.getContactInfo();
        if (!contacts.empty()) contact = contacts[0].name;
        file << v.getCompanyName() << ","
             << v.getCompanyType() << ","
             << contact << endl;
    }
    file.close();
}

void ProjectManagementSystem::saveVendorProjectRelations(const string& filename) {
    ofstream file(filename, ios::trunc);
    for (const auto& v : Vendor::getAllVendors()) {
        for (const auto* p : v.getAssignedProjects()) {
            if (p) file << v.getCompanyName() << "," << p->getName() << endl;
        }
    }
    file.close();
}

void ProjectManagementSystem::loadVendorProjectRelations(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string vname, pname;
        getline(ss, vname, ',');
        getline(ss, pname, ',');
        Vendor* v = Vendor::getVendor(vname);
        Project* p = getProject(pname);
        if (v && p) {
            v->addProject(p); // 自动双向关联
        }
    }
    file.close();
}

// ==================== Client CSV ====================
void ProjectManagementSystem::loadClientsFromCSV(const string& filename) {
    Client::getAllClients().clear();
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, type, contact;
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, contact, ',');
        if (!name.empty()) {
            vector<contactPerson> contacts = { {contact, "", ""} };
            Client::getAllClients().emplace_back(name, type, contacts);
        }
    }
    file.close();
}

void ProjectManagementSystem::saveClientsToCSV(const string& filename) {
    ofstream file(filename, ios::trunc);
    for (const auto& c : Client::getAllClients()) {
        file << c.getCompanyName() << ","
             << c.getCompanyType() << ","
             << (c.getContactInfo().empty() ? "" : c.getContactInfo()[0].name) << endl;
    }
    file.close();
}

void ProjectManagementSystem::saveClientProjectRelations(const string& filename) {
    ofstream file(filename, ios::trunc);
    for (const auto& c : Client::getAllClients()) {
        for (const auto* p : c.getProjects()) {
            if (p) file << c.getCompanyName() << "," << p->getName() << endl;
        }
    }
    file.close();
}

void ProjectManagementSystem::loadClientProjectRelations(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cname, pname;
        getline(ss, cname, ',');
        getline(ss, pname, ',');
        Client* c = Client::getClient(cname);
        Project* p = getProject(pname);
        if (c && p) {
            c->addProject(p); // 自动双向关联
        }
    }
    file.close();
}



