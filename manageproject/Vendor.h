#ifndef VENDOR_H
#define VENDOR_H

#include "Company.h"
#include "Task.h"
#include <vector>
#include <string>

using namespace std;

class Vendor : public Company {
private:
    vector<Task*> assignedTasks;                // 原始指针替代 weak_ptr
    static vector<Vendor> vendors;              // 不再使用 shared_ptr

public:
    Vendor(const string& name = "",
           const string& type = "",
           const string& contact = "");

    // CRUD operations
    bool add() override;
    bool update() override;
    bool remove() override;
    void display() const override;

    // Task management
    bool assignTask(Task* task);                     // 使用原始指针
    bool removeTask(const string& taskName);
    vector<Task*> getAssignedTasks() const;

    // Static methods
    static Vendor* getVendor(const string& vendorName);
    static vector<Vendor>& getAllVendors();
    static bool saveToFile(const string& filename);
    static bool loadFromFile(const string& filename);
};

#endif // VENDOR_H
