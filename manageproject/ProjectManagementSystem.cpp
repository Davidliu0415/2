#include "ProjectManagementSystem.h"
#include <algorithm>

ProjectManagementSystem::ProjectManagementSystem() {
    cout << "Project Management System Started\n";
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
void ProjectManagementSystem::ProjectManage() {
    while (true) {
        cout << "\n=== Project Management ===" << endl;
        cout << "1. Add Project" << endl;
        cout << "2. Modify Project" << endl;
        cout << "3. Delete Project" << endl;
        cout << "4. Display All Projects" << endl;//修饰
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
                    cout << " Project added successfully!" << endl;
                } else {
                    cout << " Project with same name already exists!" << endl;
                }
                break;

            case 2: {
                    cout << "Enter project name to modify: ";
                    cin.ignore();  // 清除缓冲区
                    string name;
                    getline(cin, name);

                    bool found = false;

                    for (auto& project : projects) {
                        if (project.getName() == name) {
                            project.update();  // 找到后调用 update()
                            found = true;
                            break;
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
                        cin.ignore();  // 忽略前面遗留的换行符
                        getline(cin, name);

                        bool deleted = false;
                        for (auto it = projects.begin(); it != projects.end(); ++it) {
                            if (it->getName() == name) {
                                projects.erase(it);
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
                } else {
                    cout << " Task with same name already exists." << endl;
                }
                break;

            case 2:
                cout << "Enter task name to modify: ";
                getline(cin, tname);
                if (Task* t = project->getTask(tname)) {
                    t->update();
                } else {
                    cout << " Task not found." << endl;
                }
                break;

            case 3:
                cout << "Enter task name to delete: ";
                getline(cin, tname);
                if (!project->removeTask(tname)) {
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
                        case 1: t->addSubtask(); break;
                        case 2: t->updateSubtask(); break;
                        case 3: t->removeSubtask(); break;
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
                } else {
                    cout << " Member with same name already exists." << endl;
                }
                break;

            case 2:
                cout << "Enter member name to modify: ";
                getline(cin, mname);
                if (TeamMember* m = project->getTeamMember(mname)) {
                    m->update();
                } else {
                    cout << " Member not found." << endl;
                }
                break;

            case 3:
                cout << "Enter member name to delete: ";
                getline(cin, mname);
                if (!project->removeTeamMember(mname)) {
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



