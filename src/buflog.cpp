/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#include <buflog.h>

#include <string>
#include <vector>

#include "./sharedbuffer.h"

namespace buflog {

Logger::Logger(const std::string filename, const int size)
    : buf(nullptr) {
    buf = new SharedBuffer(filename, size);
}
Logger::~Logger() {
    delete buf;
}

void Logger::Log(std::string msg) {
    if (buf) {
        buf->Write(msg);
    }
}

int Logger::Flush() {
    std::vector<char> cpbuf;
    buf->Copy(cpbuf);

    return 0;
}
}  // namespace buflog
