#ifndef PT_H
#define PT_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

class PT {
protected:
    string name;
    string description;
    string startDate;
    string endDate;
    string status;

public:
    PT(const string& name = "", 
             const string& description = "",
             const string& startDate = "",
             const string& endDate = "",
             const string& status = "Not Started");

    virtual ~PT() = default;

    // Getters
    string getName() const { return name; }
    string getDescription() const { return description; }
    string getStartDate() const { return startDate; }
    string getEndDate() const { return endDate; }
    string getStatus() const { return status; }

    // Setters
    virtual void setName(const string& newName) { name = newName; }
    virtual void setDescription(const string& newDescription) { description = newDescription; }
    virtual void setStartDate(const string& newStartDate) { startDate = newStartDate; }
    virtual void setEndDate(const string& newEndDate) { endDate = newEndDate; }
    virtual void setStatus(const string& newStatus) { status = newStatus; }

    // Virtual methods for CRUD operations
    virtual void display() const = 0;

    // Static method to validate date format
    static bool isValidDate(const string& date);
};

#endif // BASE_ITEM_H 