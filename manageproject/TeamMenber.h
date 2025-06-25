#ifndef TEAM_MEMBER_H
#define TEAM_MEMBER_H

#include <string>
#include <vector>

using namespace std;

class TeamMember {
private:
    string name;
    string role;
    string contactInfo;
    string memberID;
    string projectID;
    // Project* assignedProject = nullptr;  // 使用原始指针
    // static vector<TeamMember> teamMembers;

public:
    TeamMember(const string& memberID = "", const string& projectID = "", const string& name = "", const string& role = "", const string& contactInfo = "");

    // Getters
    string getName() const { return name; }
    string getRole() const { return role; }
    string getContactInfo() const { return contactInfo; }
    string getMemberID() const { return memberID; }
    string getProjectID() const { return projectID; }

    // Setters
    void setName(const string& newName) { name = newName; }
    void setRole(const string& newRole) { role = newRole; }
    void setContactInfo(const string& newContactInfo) { contactInfo = newContactInfo; }
    void setMemberID(const string& id) { memberID = id; }
    void setProjectID(const string& id) { projectID = id; }

    // CRUD operations
    void add();
    void update();
    void remove();
    void display() const;

    static TeamMember fromCSV(const string& line);
    string toCSV() const;

    // Static methods
    // static TeamMember* getTeamMember(const string& memberName);
    // static vector<TeamMember>& getAllTeamMembers();
    // static bool saveToFile(const string& filename);
    // static bool loadFromFile(const string& filename);
};

#endif // TEAM_MEMBER_H
