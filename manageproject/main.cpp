#include "ProjectManagementSystem.h"
#include "CompanyManagementSystem.h"
#include "Logger.h"
#include <iostream>
#include <string>
#include <vector>

// 用户类型枚举
enum UserType {
    GUEST = 0,
    USER = 1,
    ADMIN = 2
};

// 全局变量
UserType currentUserType = GUEST;
string currentUserName = "";

// 登录函数
bool login(ProjectManagementSystem& pms) {
    while (true) {
        cout << "\n=== Login System ===" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. User Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Please select: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 0:
                return false;
            case 1: {
                // 管理员登录
                cout << "Enter admin password: ";
                string password;
                getline(cin, password);
                
                if (password == "123456") {
                    currentUserType = ADMIN;
                    currentUserName = "Admin";
                    cout << "Admin login successful!" << endl;
                    Logger::log("ADMIN LOGIN: Admin logged in successfully");
                    return true;
                } else {
                    cout << "Invalid password! Please try again." << endl;
                    Logger::log("ADMIN LOGIN: Failed login attempt");
                    continue; // 继续循环，让用户重新选择
                }
            }
            case 2: {
                // 用户登录
                cout << "Enter username: ";
                string username;
                getline(cin, username);
                
                if (username.empty()) {
                    cout << "Username cannot be empty! Please try again." << endl;
                    continue; // 继续循环，让用户重新输入
                }
                
                // 在Project中查找用户（这里假设用户是TeamMember）
                bool userFound = false;
                
                // 遍历所有项目查找用户
                for (const auto& project : pms.getProjects()) {
                    for (const auto& member : project.getTeamMembers()) {
                        if (member.getName() == username) {
                            userFound = true;
                            break;
                        }
                    }
                    if (userFound) break;
                }
                
                if (userFound) {
                    currentUserType = USER;
                    currentUserName = username;
                    cout << "User login successful! Welcome, " << username << endl;
                    Logger::log("USER LOGIN: " + username + " logged in successfully");
                    return true;
                } else {
                    cout << "User not found! Please check your username and try again." << endl;
                    Logger::log("USER LOGIN: Failed login attempt for user " + username);
                    continue; // 继续循环，让用户重新输入
                }
            }
            default:
                cout << "Invalid option! Please try again." << endl;
                continue; // 继续循环，让用户重新选择
        }
    }
}

// 显示用户菜单（根据用户类型）
void showUserMenu() {
    cout << "\n=== Main Menu ===" << endl;
    cout << "Current User: " << currentUserName << " (" << 
         (currentUserType == ADMIN ? "Admin" : "User") << ")" << endl;
    
    if (currentUserType == ADMIN) {
        // 管理员菜单 - 所有功能
        cout << "1. Project Management" << endl;
        cout << "2. Task Management" << endl;
        cout << "3. Team Member Management" << endl;
        cout << "4. Company Management" << endl;
        cout << "5. View System Log" << endl;
        cout << "6. Logout" << endl;
        cout << "0. Exit Program" << endl;
    } else {
        // 用户菜单 - 只有显示功能
        cout << "1. Display All Projects" << endl;
        cout << "2. Display Project Details" << endl;
        cout << "3. Display My Tasks" << endl;
        cout << "4. View System Log" << endl;
        cout << "5. Logout" << endl;
        cout << "0. Exit Program" << endl;
    }
    cout << "Please select: ";
}

// 用户功能菜单
void userMenu(ProjectManagementSystem& pms) {
    while (true) {
        showUserMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 0:
                cout << "Goodbye!" << endl;
                Logger::close();
                exit(0);
            case 1: {
                // 显示所有项目
                cout << "\n=== All Projects ===" << endl;
                for (const auto& project : pms.getProjects()) {
                    cout << "Project: " << project.getName() << endl;
                    cout << "Description: " << project.getDescription() << endl;
                    cout << "Status: " << project.getStatus() << endl;
                    cout << "-------------------" << endl;
                }
                Logger::log("USER ACTION: " + currentUserName + " viewed all projects");
                break;
            }
            case 2: {
                // 显示项目详情
                cout << "Enter project name to view details: ";
                string projectName;
                getline(cin, projectName);
                
                Project* project = pms.getProject(projectName);
                if (project) {
                    project->display();
                    Logger::log("USER ACTION: " + currentUserName + " viewed project " + projectName);
                } else {
                    cout << "Project not found!" << endl;
                }
                break;
            }
            case 3: {
                // 显示用户的任务
                cout << "\n=== My Tasks ===" << endl;
                bool foundTasks = false;
                
                for (const auto& project : pms.getProjects()) {
                    for (const auto& task : project.getTasks()) {
                        // 这里可以扩展为根据任务分配显示
                        cout << "Project: " << project.getName() << " - Task: " << task.getName() << endl;
                        foundTasks = true;
                    }
                }
                
                if (!foundTasks) {
                    cout << "No tasks found." << endl;
                }
                Logger::log("USER ACTION: " + currentUserName + " viewed their tasks");
                break;
            }
            case 4:
                Logger::displayLog();
                break;
            case 5:
                cout << "Logged out successfully!" << endl;
                Logger::log("LOGOUT: " + currentUserName + " logged out");
                currentUserType = GUEST;
                currentUserName = "";
                return;
            default:
                cout << "Invalid option!" << endl;
        }
    }
}

// 管理员功能菜单
void adminMenu(ProjectManagementSystem& pms, CompanyManagementSystem& cms) {
    while (true) {
        showUserMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 0:
                cout << "Goodbye!" << endl;
                Logger::close();
                exit(0);
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
            case 5:
                Logger::displayLog();
                break;
            case 6:
                cout << "Logged out successfully!" << endl;
                Logger::log("LOGOUT: Admin logged out");
                currentUserType = GUEST;
                currentUserName = "";
                return;
            default: 
                cout << "Invalid option!" << endl;
        }
    }
}

int main() {
    // 初始化日志系统
    Logger::initialize();
    
    ProjectManagementSystem pms;
    CompanyManagementSystem cms(&pms.getProjects());

    while (true) {
        if (currentUserType == GUEST) {
            // 未登录状态，显示登录菜单
            if (!login(pms)) {
                cout << "Login failed or cancelled. Exiting..." << endl;
                Logger::close();
                return 0;
            }
        }
        
        // 根据用户类型显示相应菜单
        if (currentUserType == ADMIN) {
            adminMenu(pms, cms);
        } else if (currentUserType == USER) {
            userMenu(pms);
        }
    }
}

