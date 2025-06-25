#ifndef CLIENT_H
#define CLIENT_H

#include "Company.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Project; // 前向声明

class Client : public Company {
private:
    vector<Project*> projects;         // 原始指针管理所参与项目
    static vector<Client> clients;     // 静态存储所有 Client 对象
    string clientID;
    string projectID;

public:
    // 构造函数（支持联系人列表）
    Client(const string& clientID = "", const string& projectID = "", const string& name = "", const string& type = "", const vector<contactPerson>& contacts = {});

    // ========== 项目信息 ==========
    bool addProject(Project* project);
    bool removeProject(const string& projectName);
    vector<Project*> getProjects() const;

    // ========== 客户增删改查 ==========
    bool add() override;
    bool update() override;
    bool remove() override;
    void display() const override;

    // ========== 静态方法 ==========
    static Client* getClient(const string& clientName);
    static vector<Client>& getAllClients();
    static bool saveToFile(const string& filename);
    static bool loadFromFile(const string& filename);
    static void removeClientFromAllProjects(Client* c, std::vector<Project>& projects);

    void setClientID(const string& id) { clientID = id; }
    string getClientID() const { return clientID; }
    void setProjectID(const string& id) { projectID = id; }
    string getProjectID() const { return projectID; }
    static Client fromCSV(const string& line);
    string toCSV() const;
};

#endif // CLIENT_H
