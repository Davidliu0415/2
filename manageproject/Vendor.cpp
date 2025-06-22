#include "Vendor.h"
#include "Project.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector<Vendor> Vendor::vendors;

Vendor::Vendor(const string& name, const string& type, const string& contact)
    : Company(name, type, {contactPerson{contact, "", ""}}) {}

bool Vendor::add() {
    cout << "Enter vendor name: ";
    getline(cin, companyName);
    if (companyName.empty()) {
        cout << "Vendor name cannot be empty!" << endl;
        return false;
    }
    
    cout << "Enter vendor type: ";
    getline(cin, companyType);
    if (companyType.empty()) {
        companyType = "Unknown";
    }
    
    string contact;
    cout << "Enter contact person: ";
    getline(cin, contact);
    if (contact.empty()) {
        contact = "Unknown";
    }
    
    contactInfo.clear();
    contactInfo.push_back({contact, "", ""});
    cout << "Vendor information added successfully!" << endl;
    return true;
}

bool Vendor::update() {
    string input;
    cout << "Enter new vendor name (or q to keep): ";
    getline(cin, input);
    if (input != "q" && !input.empty()) companyName = input;
    cout << "Enter new vendor type (or q to keep): ";
    getline(cin, input);
    if (input != "q" && !input.empty()) companyType = input;
    cout << "Enter new contact person (or q to keep): ";
    getline(cin, input);
    if (input != "q" && !input.empty()) contactInfo[0].name = input;
    return true;
}

bool Vendor::remove() {
    auto& all = vendors;
    for (auto it = all.begin(); it != all.end(); ++it) {
        if (it->companyName == companyName) {
            all.erase(it);
            cout << "Vendor removed." << endl;
            return true;
        }
    }
    cout << "Vendor not found." << endl;
    return false;
}

void Vendor::display() const {
    cout << "Vendor: " << companyName << ", Type: " << companyType << ", Contact: ";
    if (!contactInfo.empty()) cout << contactInfo[0].name;
    cout << ", Projects: ";
    for (const auto* p : assignedProjects) {
        if (p) cout << p->getName() << " ";
    }
    cout << endl;
}

bool Vendor::assignTask(Task* task) {
    assignedTasks.push_back(task);
    return true;
}

bool Vendor::removeTask(const string& taskName) {
    for (auto it = assignedTasks.begin(); it != assignedTasks.end(); ++it) {
        if ((*it)->getName() == taskName) {
            assignedTasks.erase(it);
            return true;
        }
    }
    return false;
}

vector<Task*> Vendor::getAssignedTasks() const {
    return assignedTasks;
}

Vendor* Vendor::getVendor(const string& vendorName) {
    for (auto& v : vendors) {
        if (v.companyName == vendorName) return &v;
    }
    return nullptr;
}

vector<Vendor>& Vendor::getAllVendors() {
    return vendors;
}

bool Vendor::addProject(Project* project) {
    if (std::find(assignedProjects.begin(), assignedProjects.end(), project) == assignedProjects.end()) {
        assignedProjects.push_back(project);
        project->addVendor(this);
        return true;
    }
    return false;
}

bool Vendor::removeProject(Project* project) {
    assignedProjects.erase(std::remove(assignedProjects.begin(), assignedProjects.end(), project), assignedProjects.end());
    project->removeVendor(this);
    return true;
}

vector<Project*> Vendor::getAssignedProjects() const {
    return assignedProjects;
} 