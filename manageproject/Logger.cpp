#include "Logger.h"
#include <sstream>
#include <iomanip>
#include <fstream>

string Logger::logFileName = "log.csv";
bool Logger::isInitialized = false;

void Logger::initialize(const string& filename) {
    if (!isInitialized) {
        logFileName = filename;
        // 检查文件是否存在，不存在则写入表头
        std::ifstream infile(logFileName);
        if (!infile.good()) {
            std::ofstream outfile(logFileName);
            if (outfile.is_open()) {
                outfile << "时间,内容" << std::endl;
                outfile.close();
            }
        }
        isInitialized = true;
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
    if (!isInitialized) initialize(logFileName);
    string timeStr = getCurrentTime();
    ofstream file(logFileName, ios::app);
    if (file.is_open()) {
        file << '"' << timeStr << '"' << ',' << '"' << message << '"' << std::endl;
        file.close();
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
    if (isInitialized) {
        log("=== Project Management System Closed ===");
        isInitialized = false;
    }
}

void Logger::displayLog() {
    ifstream file(logFileName);
    if (!file.is_open()) {
        cout << "无法打开日志文件！" << endl;
        return;
    }
    string line;
    cout << "\n=== 日志内容 (log.csv) ===" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
} 