/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#ifndef SRC_SHAREDBUFFER_H_
#define SRC_SHAREDBUFFER_H_

#include <string>

namespace buflog {

class SharedBuffer {
 public:
    SharedBuffer(const std::string name, const int size);
    ~SharedBuffer();
    void Write(std::string msg);

 private:
    int shmid;
    void* shmaddr;
    int bufsize;
    uint64_t writeaddr;
    std::string errstr;
};
}  // namespace buflog
#endif  // SRC_SHAREDBUFFER_H_
