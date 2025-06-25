#include "Client.h"
#include "Project.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector<Client> Client::clients;

bool Client::addProject(Project* project) {
    if (std::find(projects.begin(), projects.end(), project) == projects.end()) {
        projects.push_back(project);
        project->addClient(this);
        return true;
    }
    return false;
}

bool Client::removeProject(const string& projectName) {
    for (auto it = projects.begin(); it != projects.end(); ++it) {
        if ((*it)->getName() == projectName) {
            (*it)->removeClient(this);
            projects.erase(it);
            return true;
        }
    }
    return false;
}

vector<Project*> Client::getProjects() const {
    return projects;
}

bool Client::add() {
    cout << "Enter client name: ";
    getline(cin, companyName);
    if (companyName.empty()) {
        cout << "Client name cannot be empty!" << endl;
        return false;
    }
    
    cout << "Enter client type: ";
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
    cout << "Client information added successfully!" << endl;
    return true;
}

bool Client::update() {
    string input;
    cout << "Enter new client name (or q to keep): ";
    getline(cin, input);
    if (input != "q" && !input.empty()) companyName = input;
    cout << "Enter new client type (or q to keep): ";
    getline(cin, input);
    if (input != "q" && !input.empty()) companyType = input;
    cout << "Enter new contact person (or q to keep): ";
    getline(cin, input);
    if (input != "q" && !input.empty()) contactInfo[0].name = input;
    return true;
}

bool Client::remove() {
    auto& all = clients;
    for (auto it = all.begin(); it != all.end(); ++it) {
        if (it->companyName == companyName) {
            all.erase(it);
            cout << "Client removed." << endl;
            return true;
        }
    }
    cout << "Client not found." << endl;
    return false;
}

void Client::display() const {
    cout << "Client: " << companyName << ", Type: " << companyType << ", Contact: ";
    if (!contactInfo.empty()) cout << contactInfo[0].name;
    cout << ", Projects: ";
    for (const auto* p : projects) {
        if (p) cout << p->getName() << " ";
    }
    cout << endl;
}

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n\"");
    size_t end = s.find_last_not_of(" \t\r\n\"");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

Client* Client::getClient(const string& clientName) {
    std::string key = trim(clientName);
    for (auto& c : clients) {
        if (trim(c.companyName) == key) return &c;
    }
    return nullptr;
}

vector<Client>& Client::getAllClients() {
    return clients;
} 