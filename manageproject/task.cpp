#include "Task.h"
#include <iostream>
#include <algorithm>

using namespace std;

Task::Task(const string& name,
           const string& description,
           const string& startDate,
           const string& endDate,
           const string& status)
    : PT(name, description, startDate, endDate, status) {}

// 添加任务（此处为示例，可与项目逻辑结合）
void Task::add() {
    
    cin.ignore();  // 清空前一次 cin 后残留的换行符

    cout << "请输入项目名称：" << endl;
    getline(cin, name);

    cout << "请输入项目描述：" << endl;
    getline(cin, description);

    cout << "请输入项目开始日期 (YYYY-MM-DD)：" << endl;
    getline(cin, startDate);

    cout << "请输入项目结束日期 (YYYY-MM-DD)：" << endl;
    getline(cin, endDate);

    cout << "请输入项目状态（如 Not Started/In Progress/Completed）：" << endl;
    getline(cin, status);

    cout << "项目添加成功！" << endl;
}



// 更新任务信息
void Task::update() {
    cin.ignore(); // 清理前一输入残留的换行符

    string input;
    cout << " 正在更新任务：" << name << endl;

    cout << "请输入新任务描述（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        description = input;
    }

    cout << "请输入新开始日期 (YYYY-MM-DD)（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        startDate = input;
    }

    cout << "请输入新结束日期 (YYYY-MM-DD)（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        endDate = input;
    }

    cout << "请输入新任务状态（如 Not Started/In Progress/Completed）（或输入 q 保持原值）：" << endl;
    getline(cin, input);
    if (input != "q" && !input.empty()) {
        status = input;
    }

    cout << " 任务更新成功。" << endl;
}


// 移除任务（本地逻辑）
void Task::remove() {
    cout << "任务 [" << name << "] 被标记为删除（逻辑操作，仅限本地）" << endl;
}

// 显示任务详情
void Task::display() const {
    cout << "\n任务名称: " << name << endl;
    cout << "描述: " << description << endl;
    cout << "开始日期: " << startDate << endl;
    cout << "结束日期: " << endDate << endl;
    cout << "状态: " << status << endl;

    if (!subtasks.empty()) {
        cout << "子任务列表:" << endl;
        for (const auto& sub : subtasks) {
            sub.display();
        }
    }
}

// ========== 子任务管理 ==========

bool Task::addSubtask(const Task& subtask) {
    auto it = find_if(subtasks.begin(), subtasks.end(),
                      [&subtask](const Task& t) { return t.getName() == subtask.getName(); });

    if (it != subtasks.end()) {
        return false;  // 已存在相同名称的子任务
    }

    subtasks.push_back(subtask);
    return true;
}

bool Task::removeSubtask(const string& subtaskName) {
    auto it = find_if(subtasks.begin(), subtasks.end(),
                      [&subtaskName](const Task& t) { return t.getName() == subtaskName; });

    if (it == subtasks.end()) {
        return false;
    }

    subtasks.erase(it);
    return true;
}

bool Task::updateSubtask(const string& subtaskName, const Task& newSubtask) {
    auto it = find_if(subtasks.begin(), subtasks.end(),
                      [&subtaskName](const Task& t) { return t.getName() == subtaskName; });

    if (it == subtasks.end()) {
        return false;
    }

    *it = newSubtask;
    return true;
}

Task* Task::getSubtask(const string& subtaskName) {
    auto it = find_if(subtasks.begin(), subtasks.end(),
                      [&subtaskName](const Task& t) { return t.getName() == subtaskName; });

    return (it != subtasks.end()) ? &(*it) : nullptr;
}
