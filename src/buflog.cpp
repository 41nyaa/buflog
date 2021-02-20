/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#include "buflog.h"

#include "sharedbuffer.h"

namespace buflog {

Logger::Logger(const std::string filename, const int size)
    : bufptr(NULL) {
    bufptr = new SharedBuffer(filename, size);
}
Logger::~Logger() {
    delete bufptr;
}

void Logger::Log(std::string msg) {

}

int Logger::Flush() {
    return 0;
}
}   /* buflog */
