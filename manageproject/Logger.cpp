#include "Logger.h"
#include <sstream>
#include <iomanip>

string Logger::logFileName = "project_management.log";
ofstream Logger::logFile;
bool Logger::isInitialized = false;

void Logger::initialize(const string& filename) {
    if (!isInitialized) {
        logFileName = filename;
        logFile.open(logFileName, ios::app);
        if (logFile.is_open()) {
            isInitialized = true;
            log("=== Project Management System Started ===");
        } else {
            cerr << "Failed to open log file: " << logFileName << endl;
        }
    }
}

string Logger::getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    stringstream ss;
    ss << setfill('0') << setw(4) << (1900 + ltm->tm_year) << "-"
       << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "-"
       << setfill('0') << setw(2) << ltm->tm_mday << " "
       << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min << ":"
       << setfill('0') << setw(2) << ltm->tm_sec;
    
    return ss.str();
}

void Logger::log(const string& message) {
    if (isInitialized && logFile.is_open()) {
        logFile << "[" << getCurrentTime() << "] " << message << endl;
        logFile.flush(); // 确保立即写入文件
    }
}

void Logger::logProjectOperation(const string& operation, const string& projectName) {
    string message = "PROJECT: " + operation + " - " + projectName;
    log(message);
}

void Logger::logTaskOperation(const string& operation, const string& taskName, const string& projectName) {
    string message = "TASK: " + operation + " - " + taskName + " (Project: " + projectName + ")";
    log(message);
}

void Logger::logTeamMemberOperation(const string& operation, const string& memberName, const string& projectName) {
    string message = "TEAM MEMBER: " + operation + " - " + memberName + " (Project: " + projectName + ")";
    log(message);
}

void Logger::logVendorOperation(const string& operation, const string& vendorName) {
    string message = "VENDOR: " + operation + " - " + vendorName;
    log(message);
}

void Logger::logClientOperation(const string& operation, const string& clientName) {
    string message = "CLIENT: " + operation + " - " + clientName;
    log(message);
}

void Logger::logSubtaskOperation(const string& operation, const string& subtaskName, const string& taskName) {
    string message = "SUBTASK: " + operation + " - " + subtaskName + " (Task: " + taskName + ")";
    log(message);
}

void Logger::close() {
    if (isInitialized && logFile.is_open()) {
        log("=== Project Management System Closed ===");
        logFile.close();
        isInitialized = false;
    }
}

void Logger::displayLog() {
    ifstream readFile(logFileName);
    if (readFile.is_open()) {
        cout << "\n=== System Log ===" << endl;
        string line;
        while (getline(readFile, line)) {
            cout << line << endl;
        }
        readFile.close();
    } else {
        cout << "Log file not found or cannot be opened." << endl;
    }
}

void Logger::logToCSV(const string& message, const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << getCurrentTime() << "," << message << endl;
        file.close();
    }
}

void Logger::displayCSVLog(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "\n=== CSV System Log ===" << endl;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "CSV Log file not found or cannot be opened." << endl;
    }
} 