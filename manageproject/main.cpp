#include "ProjectManagementSystem.h"
#include "CompanyManagementSystem.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    ProjectManagementSystem pms;
    CompanyManagementSystem cms(&pms.getProjects());

    while (true) {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Project Management" << endl;
        cout << "2. Task Management" << endl;
        cout << "3. Team Member Management" << endl;
        cout << "4. Company Management" << endl;
        cout << "0. Exit Program" << endl;
        cout << "Please select: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: 
                pms.ProjectManage(); 
                break;
            case 2: 
                pms.TaskManage(); 
                break;
            case 3: 
                pms.TeamMemberManage(); 
                break;
            case 4:
                cms.menu();
                break;
            case 0: 
                cout << "Goodbye!" << endl;
                return 0;
            default: 
                cout << "Invalid option" << endl;
        }
    }
}

