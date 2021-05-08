/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#include <buflog.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "./ipcsharedbuffer.h"

namespace buflog {

Logger::Logger(const std::string filename, const int size)
    : buf(nullptr)
    , filename(filename) {

    std::ofstream ofs(filename.c_str(), std::ofstream::out);
    ofs.close();

    buf = new IPCSharedBuffer(filename, size);
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

    std::ofstream ofs(filename.c_str(), std::ofstream::out);
    ofs.write(cpbuf.data(), cpbuf.size());
    ofs.close();
    if(ofs.bad()) {
        return errno;
    }

    return 0;
}

bool Logger::Fail(std::string& error) {
    return buf->Fail(error);
}
}  // namespace buflog
