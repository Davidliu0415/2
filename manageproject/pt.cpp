#include "pt.h"

PT::PT(const string& name, 
       const string& description,
       const string& startDate,
       const string& endDate,
       const string& status)
    : name(name),
      description(description),
      startDate(startDate),
      endDate(endDate),
      status(status) {}

bool PT::isValidDate(const string& date) {
    // 简单的日期格式验证 (YYYY-MM-DD)
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    // 检查年份
    for (int i = 0; i < 4; i++) {
        if (!isdigit(date[i])) return false;
    }
    
    // 检查月份
    for (int i = 5; i < 7; i++) {
        if (!isdigit(date[i])) return false;
    }
    
    // 检查日期
    for (int i = 8; i < 10; i++) {
        if (!isdigit(date[i])) return false;
    }
    
    return true;
} 