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
    : filename(filename)
    , buf(nullptr) {

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

    std::ofstream ofs(filename.c_str(), std::ofstream::app);
    ofs << cpbuf.data();
    ofs.close();
    if(ofs.bad())    //bad() function will check for badbit
    {
        std::cout << "Error: " << errno;
    }

    return 0;
}

bool Logger::Fail(std::string& error) {
    return buf->Fail(error);
}
}  // namespace buflog
