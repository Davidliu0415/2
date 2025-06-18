#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct contactPerson {
    string name;
    string phone;
    string email;
};

class Company {
protected:
    string companyName;
    string companyType;
    vector<contactPerson> contactInfo;  // 多个联系人
    static vector<Company> companies;

public:
    Company(const string& name = "",
            const string& type = "",
            const vector<contactPerson>& contacts = {})
        : companyName(name), companyType(type), contactInfo(contacts) {}

    virtual ~Company() = default;

    // Getters
    string getCompanyName() const { return companyName; }
    string getCompanyType() const { return companyType; }
    vector<contactPerson> getContactInfo() const { return contactInfo; }

    // Setters
    virtual void setCompanyName(const string& name) { companyName = name; }
    virtual void setCompanyType(const string& type) { companyType = type; }
    virtual void setContactInfo(const vector<contactPerson>& contacts) { contactInfo = contacts; }

    // Virtual CRUD operations
    virtual bool add() = 0;
    virtual bool update() = 0;
    virtual bool remove() = 0;
    virtual void display() const = 0;

    // Static methods
    static Company* getCompany(const string& name);
    static vector<Company>& getAllCompanies();
    static bool saveToFile(const string& filename);
    static bool loadFromFile(const string& filename);
};

#endif // COMPANY_H
