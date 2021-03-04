/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#ifndef SRC_ISHAREDBUFFER_H_
#define SRC_ISHAREDBUFFER_H_

#include <string>
#include <vector>

namespace buflog {

class ISharedBuffer {
 public:
    virtual ~ISharedBuffer() {};
    virtual void Write(std::string& msg) = 0;
    virtual void Copy(std::vector<char>& buf) = 0;
    bool Fail(std::string& error) {
        error = errstr;
        return errstr.empty() ? false : true;
    }

 protected:
    std::string errstr;
};

}  // namespace buflog
#endif  // SRC_ISHAREDBUFFER_H_
