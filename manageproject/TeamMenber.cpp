#include "TeamMenber.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// ✅ 构造函数
TeamMember::TeamMember(const string& memberID, const string& projectID, const string& name, const string& role, const string& contactInfo)
    : name(name), role(role), contactInfo(contactInfo), memberID(memberID), projectID(projectID) {}

// ✅ 添加成员（用户输入）
void TeamMember::add() {
    // cin.ignore();  // Clear the newline character from previous cin

    cout << "Enter team member name:" << endl;
    getline(cin, name);

    cout << "Enter team member role:" << endl;
    getline(cin, role);

    cout << "Enter team member contact information:" << endl;
    getline(cin, contactInfo);

    cout << "Team member added successfully!" << endl;
}

// ✅ 更新成员信息
void TeamMember::update() {
    // cin.ignore();  // Clear the newline character from previous cin

    string input;

    cout << "Enter new team member name (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        name = input;
    }

    cout << "Enter new team member role (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        role = input;
    }

    cout << "Enter new team member contact information (or enter q to keep current value):" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        contactInfo = input;
    }

    cout << "Team member information updated successfully." << endl;
}

// ✅ 删除成员（逻辑上）
void TeamMember::remove() {
    cout << "Team member [" << name << "] marked for removal." << endl;
    // 如果你用静态 vector<TeamMember>，你可以在外部调用 erase 来真正删除
}

// ✅ 显示成员信息
void TeamMember::display() const {
    cout << "\nTeam Member Information:" << endl;
    cout << "Name: " << name << endl;
    cout << "Role: " << role << endl;
    cout << "Contact Info: " << contactInfo << endl;
}

TeamMember TeamMember::fromCSV(const string& line) {
    stringstream ss(line);
    string memberID, projectID, name, role, contactInfo;
    getline(ss, memberID, ',');
    getline(ss, projectID, ',');
    getline(ss, name, ',');
    getline(ss, role, ',');
    getline(ss, contactInfo, ',');
    return TeamMember(memberID, projectID, name, role, contactInfo);
}

string TeamMember::toCSV() const {
    return memberID + "," + projectID + "," + name + "," + role + "," + contactInfo;
}
