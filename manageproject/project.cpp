#include "project.h"
#include "Vendor.h"
#include "Client.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>


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

    cout << "\nVendors:" << endl;
    if (vendors.empty()) {
        cout << "  None" << endl;
    } else {
        for (const auto* v : vendors) {
            if (v) v->display();
        }
    }

    cout << "\nClients:" << endl;
    if (clients.empty()) {
        cout << "  None" << endl;
    } else {
        for (const auto* c : clients) {
            if (c) c->display();
        }
    }
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

// Const versions
const vector<Task>& Project::getTasks() const {
    return tasks;
}
const vector<TeamMember>& Project::getTeamMembers() const {
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

// 静态方法：保存所有项目到project.csv
bool Project::saveToCSV(const std::vector<Project>& projects, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    // 写表头
    file << "项目名,描述,开始日期,结束日期,状态" << std::endl;
    for (const auto& p : projects) {
        file << '"' << p.getName() << '"' << ','
             << '"' << p.getDescription() << '"' << ','
             << '"' << p.getStartDate() << '"' << ','
             << '"' << p.getEndDate() << '"' << ','
             << '"' << p.getStatus() << '"' << std::endl;
    }
    file.close();
    return true;
}

// 静态方法：从CSV加载所有项目
bool Project::loadFromCSV(std::vector<Project>& projects, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;
    getline(file, line); // 跳过表头
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name, desc, start, end, status;
        getline(ss, name, ',');
        getline(ss, desc, ',');
        getline(ss, start, ',');
        getline(ss, end, ',');
        getline(ss, status, ',');
        // 去除引号
        auto trim = [](std::string& s) {
            if (!s.empty() && s.front() == '"') s.erase(0, 1);
            if (!s.empty() && s.back() == '"') s.pop_back();
        };
        trim(name); trim(desc); trim(start); trim(end); trim(status);
        projects.emplace_back(name, desc, start, end, status);
    }
    file.close();
    return true;
}

bool Project::saveAllToCSV(const std::vector<Project>& projects, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    // 写表头
    file << "type,project_name,task_name,subtask_name,member_name,role,contact,vendor_name,client_name,description,start_date,end_date,status,vendor_type,vendor_contact,client_type,client_contact" << std::endl;
    for (const auto& p : projects) {
        // 项目本身
        file << "Project," << '"' << p.getName() << '"' << ",,,,,,,," << '"' << p.getDescription() << '"' << ',' << '"' << p.getStartDate() << '"' << ',' << '"' << p.getEndDate() << '"' << ',' << '"' << p.getStatus() << '"' << std::endl;
        // 任务
        for (const auto& t : p.getTasks()) {
            file << "Task," << '"' << p.getName() << '"' << ',' << '"' << t.getName() << '"' << ",,,,,," << '"' << t.getDescription() << '"' << ',' << '"' << t.getStartDate() << '"' << ',' << '"' << t.getEndDate() << '"' << ',' << '"' << t.getStatus() << '"' << std::endl;
            // 子任务
            for (const auto& st : t.getSubtasks()) {
                file << "Subtask," << '"' << p.getName() << '"' << ',' << '"' << t.getName() << '"' << ',' << '"' << st.getName() << '"' << ",,,,,," << '"' << st.getDescription() << '"' << ',' << '"' << st.getStartDate() << '"' << ',' << '"' << st.getEndDate() << '"' << ',' << '"' << st.getStatus() << '"' << std::endl;
            }
        }
        // 成员
        for (const auto& m : p.getTeamMembers()) {
            file << "Member," << '"' << p.getName() << '"' << ",,," << '"' << m.getName() << '"' << ',' << '"' << m.getRole() << '"' << ',' << '"' << m.getContactInfo() << '"' << ",,,," << std::endl;
        }
        // 供应商
        for (const auto* v : p.getVendors()) {
            if (v) file << "Vendor," << '"' << p.getName() << '"' << ",,,,,," << '"' << v->getCompanyName() << '"' << ",,,,"
                << '"' << v->getCompanyType() << '"' << ','
                << '"' << (v->getContactInfo().empty() ? "" : v->getContactInfo()[0].name) << '"' << ",,," << std::endl;
        }
        // 客户
        for (const auto* c : p.getClients()) {
            if (c) file << "Client," << '"' << p.getName() << '"' << ",,,,,,," << '"' << c->getCompanyName() << '"' << ",,,,"
                << '"' << c->getCompanyType() << '"' << ','
                << '"' << (c->getContactInfo().empty() ? "" : c->getContactInfo()[0].name) << '"' << ",,," << std::endl;
        }
    }
    file.close();
    return true;
}

// 加载所有数据（仅实现Project/Task/Member，子任务/供应商/客户可后续补充）
bool Project::loadAllFromCSV(std::vector<Project>& projects, const std::string& filename) {
    // 1. 先清空并重建Vendor/Client静态数组
    Vendor::getAllVendors().clear();
    Client::getAllClients().clear();

    // 2. 第一遍遍历CSV，收集所有Vendor/Client对象
    std::ifstream file1(filename);
    if (!file1.is_open()) return false;
    std::string line;
    getline(file1, line); // 跳过表头
    while (getline(file1, line)) {
        std::stringstream ss(line);
        std::string type, pname, tname, stname, mname, role, contact, vname, cname, desc, sdate, edate, status, vtype, vcontact, ctype, ccontact;
        getline(ss, type, ','); getline(ss, pname, ','); getline(ss, tname, ','); getline(ss, stname, ','); getline(ss, mname, ','); getline(ss, role, ','); getline(ss, contact, ','); getline(ss, vname, ','); getline(ss, cname, ','); getline(ss, desc, ','); getline(ss, sdate, ','); getline(ss, edate, ','); getline(ss, status, ','); getline(ss, vtype, ','); getline(ss, vcontact, ','); getline(ss, ctype, ','); getline(ss, ccontact, ',');
        auto trim = [](std::string& s) { if (!s.empty() && s.front() == '"') s.erase(0, 1); if (!s.empty() && s.back() == '"') s.pop_back(); };
        trim(vname); trim(cname); trim(vtype); trim(vcontact); trim(ctype); trim(ccontact);
        if (type == "Vendor" && !vname.empty()) {
            if (!Vendor::getVendor(vname)) {
                std::string _vname = vname; trim(_vname);
                std::string _vtype = vtype; trim(_vtype);
                std::string _vcontact = vcontact; trim(_vcontact);
                Vendor vobj(_vname, _vtype, _vcontact);
                Vendor::getAllVendors().push_back(vobj);
            }
        }
        if (type == "Client" && !cname.empty()) {
            if (!Client::getClient(cname)) {
                std::string _cname = cname; trim(_cname);
                std::string _ctype = ctype; trim(_ctype);
                std::string _ccontact = ccontact; trim(_ccontact);
                std::vector<contactPerson> contacts;
                contactPerson cp; cp.name = _ccontact; cp.phone = ""; cp.email = "";
                contacts.push_back(cp);
                Client cobj(_cname, _ctype, contacts);
                Client::getAllClients().push_back(cobj);
            }
        }
    }
    file1.close();

    // 3. 第二遍遍历CSV，加载Project及其指针关系
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    getline(file, line); // 跳过表头
    std::map<std::string, Project> project_map;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string type, pname, tname, stname, mname, role, contact, vname, cname, desc, sdate, edate, status, vtype, vcontact, ctype, ccontact;
        getline(ss, type, ','); getline(ss, pname, ','); getline(ss, tname, ','); getline(ss, stname, ','); getline(ss, mname, ','); getline(ss, role, ','); getline(ss, contact, ','); getline(ss, vname, ','); getline(ss, cname, ','); getline(ss, desc, ','); getline(ss, sdate, ','); getline(ss, edate, ','); getline(ss, status, ','); getline(ss, vtype, ','); getline(ss, vcontact, ','); getline(ss, ctype, ','); getline(ss, ccontact, ',');
        auto trim = [](std::string& s) { if (!s.empty() && s.front() == '"') s.erase(0, 1); if (!s.empty() && s.back() == '"') s.pop_back(); };
        trim(pname); trim(tname); trim(stname); trim(mname); trim(role); trim(contact); trim(vname); trim(cname); trim(desc); trim(sdate); trim(edate); trim(status); trim(vtype); trim(vcontact); trim(ctype); trim(ccontact);
        if (type == "Project") {
            project_map[pname] = Project(pname, desc, sdate, edate, status);
        } else if (type == "Task") {
            if (project_map.count(pname)) {
                project_map[pname].addTask(Task(tname, desc, sdate, edate, status));
            }
        } else if (type == "Member") {
            if (project_map.count(pname)) {
                project_map[pname].addTeamMember(TeamMember(mname, role, contact));
            }
        } else if (type == "Vendor") {
            if (project_map.count(pname)) {
                Vendor* vptr = Vendor::getVendor(vname);
                if (vptr) project_map[pname].addVendor(vptr);
            }
        } else if (type == "Client") {
            if (project_map.count(pname)) {
                Client* cptr = Client::getClient(cname);
                if (cptr) project_map[pname].addClient(cptr);
            }
        }
        // 子任务等可后续补充
    }
    projects.clear();
    for (auto& kv : project_map) projects.push_back(kv.second);
    file.close();
    return true;
}