#include "ProjectManagementSystem.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    ProjectManagementSystem pms;
    
    // Initialize some example projects
    Project project1("Project1", "This is the first project", "2024-03-20", "2024-04-20", "In Progress");
    Project project2("Project2", "This is the second project", "2024-03-21", "2024-04-21", "Not Started");

    while (true) {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Project Management" << endl;
        cout << "2. Task Management" << endl;
        cout << "3. Team Member Management" << endl;
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
            case 0: 
                cout << "Goodbye!" << endl;
                return 0;
            default: 
                cout << "Invalid option" << endl;
        }
    }
}

