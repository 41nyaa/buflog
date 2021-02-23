/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#ifndef SRC_SHAREDBUFFER_H_
#define SRC_SHAREDBUFFER_H_

#include <string>

namespace buflogtest {
    class SharedBufferTest;
}  // buflogtest

namespace buflog {

class SharedBuffer {
 public:
    SharedBuffer(const std::string name, const int size);
    ~SharedBuffer();
    void Write(std::string& msg);

 private:
    int shmid;
    void* shmaddr;
    int bufsize;
    void* writeaddr;
    std::string errstr;

    //for unittest
    friend class buflogtest::SharedBufferTest;
};

}  // namespace buflog
#endif  // SRC_SHAREDBUFFER_H_
