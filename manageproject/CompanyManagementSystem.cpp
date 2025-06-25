#include "CompanyManagementSystem.h"
#include <iostream>
#include <sstream>
#include "Logger.h"
#include "ProjectManagementSystem.h"
using namespace std;

CompanyManagementSystem::CompanyManagementSystem(vector<Project>* projects, ProjectManagementSystem* pms)
    : projects(projects), pms(pms) {}

void CompanyManagementSystem::menu() {
    // 不再创建新的pms对象，所有Vendor/Client与Project的操作都基于传入的projects指针和静态vector
    // 多对多关系的加载/保存已在main.cpp统一处理
    while (true) {
        cout << "\n=== Company Management ===" << endl;
        cout << "1. Add Vendor" << endl;
        cout << "2. Update Vendor" << endl;
        cout << "3. Delete Vendor" << endl;
        cout << "4. Show All Vendors" << endl;
        cout << "5. Add Client" << endl;
        cout << "6. Update Client" << endl;
        cout << "7. Delete Client" << endl;
        cout << "8. Show All Clients" << endl;
        cout << "9. Show CSV Log" << endl;
        cout << "0. Return to Main Menu" << endl;
        cout << "Please select: ";
        int choice;
        cin >> choice;
        cin.ignore();
        string name;
        switch (choice) {
            case 0:
                // 所有保存操作已在main.cpp统一处理
                return;
            case 1: {
                Vendor v;
                v.add();
                Vendor::getAllVendors().push_back(v);
                Logger::logToCSV("Add Vendor: " + v.getCompanyName());
                Vendor* vptr = &Vendor::getAllVendors().back();

                if (projects && !projects->empty()) {
                    cout << "\nAvailable projects:\n";
                    for (size_t i = 0; i < projects->size(); ++i)
                        cout << "  [" << i << "] " << (*projects)[i].getName() << endl;

                    cout << "\nEnter the item number to be assigned to the vendor and enter -1 to end the assignment。" << endl;
                    int idx;

                    while (true) {
                        cout << "项目编号: ";
                        cin >> idx;

                        if (cin.fail()) {
                            cin.clear();
                            string dummy;
                            cin >> dummy;
                            if (dummy == "q" || dummy == "Q") break;
                            cout << " Illegal entry, please enter a number or -1 to exit." << endl;
                            continue;
                        }

                        if (idx == -1) break;

                        if (idx >= 0 && idx < projects->size()) {
                            vptr->addProject(&(*projects)[idx]);
                            cout << "Allocated to projects: " << (*projects)[idx].getName() << endl;
                            if (pms) pms->saveVendorProjectRelations();
                        } else {
                            cout << "Invalid number, please re-enter." << endl;
                        }
                    }
                }
                
                cout << "Vendor added successfully." << endl;
                break;
            }
                case 2: {
                    cout << "Enter vendor name to update: ";
                    cin.ignore();
                    getline(cin, name);
                    Vendor* v = Vendor::getVendor(name);
                    if (v) {
                        v->update();
                        Logger::logToCSV("Update Vendor: " + v->getCompanyName());

                        if (projects && !projects->empty()) {
                            cout << "\nAvailable projects:\n";
                            for (size_t i = 0; i < projects->size(); ++i)
                                cout << "  [" << i << "] " << (*projects)[i].getName() << endl;

                            cout << "\nEnter project indices to assign to this vendor one by one." << endl;
                            cout << "Enter -1 to finish, or 'q' to skip assignment." << endl;

                            // Clear existing assignments
                            for (Project* p : v->getAssignedProjects()) {
                                p->removeVendor(v);
                            }
                            v->getAssignedProjects().clear();

                            while (true) {
                                cout << "Project index: ";
                                string input;
                                getline(cin, input);

                                if (input == "q" || input == "Q") {
                                    cout << "Skipped project assignment." << endl;
                                    break;
                                }

                                try {
                                    int idx = stoi(input);
                                    if (idx == -1) break;

                                    if (idx >= 0 && idx < projects->size()) {
                                        Project* p = &(*projects)[idx];
                                        v->addProject(p);
                                        cout << " Assigned to project: " << p->getName() << endl;
                                        if (pms) pms->saveVendorProjectRelations();
                                    } else {
                                        cout << " Invalid index. Please try again." << endl;
                                    }
                                } catch (...) {
                                    cout << " Invalid input. Please enter a number, -1 to stop, or q to skip." << endl;
                                }
                            }
                        } else {
                            cout << "No available projects to assign." << endl;
                        }
                    } else {
                        cout << " Vendor not found." << endl;
                    }
                    break;
                }

            case 3: {
                cout << "Enter vendor name to delete: ";
                getline(cin, name);
                Vendor* v = Vendor::getVendor(name);
                if (v) {
                    Logger::logToCSV("Delete Vendor: " + v->getCompanyName());
                    v->remove();
                } else cout << "Vendor not found." << endl;
                break;
            }
            case 4: {
                for (const auto& v : Vendor::getAllVendors()) v.display();
                break;
            }
            case 5: {
                Client c;
                c.add();
                Client::getAllClients().push_back(c);
                Logger::logToCSV("Add Client: " + c.getCompanyName());
                Client* cptr = &Client::getAllClients().back();

                if (projects && !projects->empty()) {
                    cout << "\nAvailable projects:\n";
                    for (size_t i = 0; i < projects->size(); ++i)
                        cout << "  [" << i << "] " << (*projects)[i].getName() << endl;

                    cout << "\nEnter project indices to assign to this client one by one." << endl;
                    cout << "Enter -1 to finish, or 'q' to skip assignment." << endl;

                    while (true) {
                        cout << "Project index: ";
                        string input;
                        getline(cin, input);

                        if (input == "q" || input == "Q") {
                            cout << "Skipped project assignment." << endl;
                            break;
                        }

                        try {
                            int idx = stoi(input);
                            if (idx == -1) break;

                            if (idx >= 0 && idx < projects->size()) {
                                Project* p = &(*projects)[idx];
                                cptr->addProject(p);
                                cout << " Assigned to project: " << p->getName() << endl;
                                if (pms) pms->saveClientProjectRelations();
                            } else {
                                cout << " Invalid index. Please try again." << endl;
                            }
                        } catch (...) {
                            cout << " Invalid input. Please enter a number, -1 to stop, or q to skip." << endl;
                        }
                    }
                }

                cout << "Client added successfully." << endl;
                break;
            }

            case 6: {
                cout << "Enter client name to update: ";
                cin.ignore();
                getline(cin, name);
                Client* c = Client::getClient(name);
                if (c) {
                    c->update();
                    Logger::logToCSV("Update Client: " + c->getCompanyName());

                    if (projects && !projects->empty()) {
                        cout << "\nAvailable projects:\n";
                        for (size_t i = 0; i < projects->size(); ++i)
                            cout << "  [" << i << "] " << (*projects)[i].getName() << endl;

                        cout << "\nEnter project indices to assign to this client one by one." << endl;
                        cout << "Enter -1 to finish, or 'q' to skip assignment." << endl;

                        // Clear old assignments
                        for (Project* p : c->getProjects()) {
                            p->removeClient(c);
                        }
                        c->getProjects().clear();

                        while (true) {
                            cout << "Project index: ";
                            string input;
                            getline(cin, input);

                            if (input == "q" || input == "Q") {
                                cout << "Skipped project assignment." << endl;
                                break;
                            }

                            try {
                                int idx = stoi(input);
                                if (idx == -1) break;

                                if (idx >= 0 && idx < projects->size()) {
                                    Project* p = &(*projects)[idx];
                                    c->addProject(p);
                                    cout << " Assigned to project: " << p->getName() << endl;
                                    if (pms) pms->saveClientProjectRelations();
                                } else {
                                    cout << " Invalid index. Please try again." << endl;
                                }
                            } catch (...) {
                                cout << " Invalid input. Please enter a number, -1 to stop, or q to skip." << endl;
                            }
                        }
                    } else {
                        cout << " No available projects to assign." << endl;
                    }
                } else {
                    cout << "Client not found." << endl;
                }
                break;
                }
            case 7: {
                cout << "Enter client name to delete: ";
                getline(cin, name);
                Client* c = Client::getClient(name);
                if (c) {
                    Logger::logToCSV("Delete Client: " + c->getCompanyName());
                    c->remove();
                } else cout << "Client not found." << endl;
                break;
            }
            case 8: {
                for (const auto& c : Client::getAllClients()) c.display();
                break;
            }
            case 9: {
                Logger::displayCSVLog();
                break;
            }
            default: cout << "Invalid option!" << endl;
        }
    }
} 