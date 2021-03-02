/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#ifndef INCLUDE_BUFLOG_H_
#define INCLUDE_BUFLOG_H_

#include <string>

namespace buflog {
class SharedBuffer;

class Logger {
 public:
    Logger(const std::string filename, const int size);
    ~Logger();
    void Log(std::string msg);
    int Flush();

 private:
    SharedBuffer* buf;
};
}  // namespace buflog
#endif  // INCLUDE_BUFLOG_H_
