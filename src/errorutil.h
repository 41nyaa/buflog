/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#ifndef SRC_ERRORUTIL_H_
#define SRC_ERRORUTIL_H_

#include <string>

namespace buflog {

inline void ToErrStr(
        std::string* errstr,
        const char* func,
        const int errnum) {
    *errstr = std::string(func) + std::string(" errno:") + std::to_string(errnum);
}

}  // namespace buflog
#endif  // SRC_ERRORUTIL_H_

