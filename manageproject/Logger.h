#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Logger {
private:
    static string logFileName;
    static ofstream logFile;
    static bool isInitialized;
    
public:
    // 初始化日志系统
    static void initialize(const string& filename = "project_management.log");
    
    // 记录不同类型的操作
    static void logProjectOperation(const string& operation, const string& projectName);
    static void logTaskOperation(const string& operation, const string& taskName, const string& projectName);
    static void logTeamMemberOperation(const string& operation, const string& memberName, const string& projectName);
    static void logVendorOperation(const string& operation, const string& vendorName);
    static void logClientOperation(const string& operation, const string& clientName);
    static void logSubtaskOperation(const string& operation, const string& subtaskName, const string& taskName);
    
    // 通用日志记录
    static void log(const string& message);
    
    // 获取当前时间字符串
    static string getCurrentTime();
    
    // 关闭日志文件
    static void close();
    
    // 显示日志内容
    static void displayLog();
};

#endif // LOGGER_H 