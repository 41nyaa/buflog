/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#ifndef SRC_IPCSHAREDBUFFER_H_
#define SRC_IPCSHAREDBUFFER_H_

#include "isharedbuffer.h"

namespace buflogtest {
    class IPCSharedBufferTest;
}  // buflogtest

namespace buflog {

class IPCSharedBuffer final : public ISharedBuffer{
 public:
    IPCSharedBuffer(const std::string name, const int size);
    ~IPCSharedBuffer();
    void Write(std::string& msg) override;
    void Copy(std::vector<char>& buf) override;

 private:
    int shmid;
    void* shmaddr;
    int bufsize;
    void* writeaddr;

    //for unittest
    friend class buflogtest::IPCSharedBufferTest;
};

}  // namespace buflog
#endif  // SRC_IPCSHAREDBUFFER_H_
