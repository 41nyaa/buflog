/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#ifndef BUFLOG_INTERNAL_ERRORUTIL_H
#define BUFLOG_INTERNAL_ERRORUTIL_H

#include <string>

namespace buflog {
    
inline void ToErrStr(std::string& errstr, const char* func, const int errnum) {
    char strerrno[128]{};

    if (-1 == strerror_r(errnum, strerrno, sizeof(strerrno))) {
        errstr = std::string(func) + std::string(" ") + std::to_string(errnum);
    }
    else {
        errstr = std::string(func) + std::string(" ") + std::string(strerrno);
    }
};

} //buflog
#endif /* BUFLOG_INTERNAL_ERRORUTIL_H */

