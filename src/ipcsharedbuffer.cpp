
/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#include "ipcsharedbuffer.h"

#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstring>

#include "errorutil.h"

namespace buflog {

IPCSharedBuffer::IPCSharedBuffer(const std::string name, const int size)
        : shmid(0)
        , shmaddr(nullptr)
        , bufsize(size) {
    key_t key = ftok(name.c_str(), 1);
    if (-1 == key) {
        ToErrStr(&errstr, __func__, errno);
        return;
    }

    shmid = shmget(key, bufsize, IPC_CREAT | 0666);
    if (-1 == shmid) {
        ToErrStr(&errstr, __func__, errno);
        return;
    }

    shmaddr = shmat(shmid, NULL, 0);
    if ((void*)-1 == shmaddr) {
        ToErrStr(&errstr, __func__, errno);
        return;
    }

    memset(shmaddr, 0x0, bufsize);
    writeaddr = shmaddr;
}

IPCSharedBuffer::~IPCSharedBuffer() {
    shmdt(shmaddr);
    if (-1 == shmctl(shmid, IPC_RMID, NULL)) {
        ToErrStr(&errstr, __func__, errno);
        return;
    }
}

void IPCSharedBuffer::Write(std::string& msg) {
    char* msgptr = const_cast<char*>(msg.c_str());
    int  msgsize = msg.size();
    int  remain = reinterpret_cast<int64_t>(writeaddr) + msgsize
                        - (reinterpret_cast<int64_t>(shmaddr) + bufsize); 
    if (remain > 0) {
        memcpy(writeaddr, msgptr, msgsize - remain);
        msgptr += msgsize - remain;

        memcpy(shmaddr, msgptr, remain);
        writeaddr = reinterpret_cast<char*>(shmaddr) + remain;
    } else {
        memcpy(writeaddr, msgptr, msgsize);
        writeaddr = (char*)writeaddr + msgsize;
    }
}

void IPCSharedBuffer::Copy(std::vector<char>& buf) {
    buf.clear();

    int formersize = reinterpret_cast<int64_t>(shmaddr) + bufsize
                            - reinterpret_cast<int64_t>(writeaddr); 
    if ( (0    == formersize                         ) ||
         ('\0' == *reinterpret_cast<char*>(writeaddr)) ) {
        buf.resize(bufsize - formersize);
        memcpy(&buf[0], shmaddr, bufsize - formersize);
    } else {
        buf.resize(bufsize);
        memcpy(&buf[0], writeaddr, formersize);

        int lattersize = reinterpret_cast<int64_t>(writeaddr) 
                            - reinterpret_cast<int64_t>(shmaddr); 
        memcpy(&buf[formersize], shmaddr, lattersize);
    }
}
}  /// namespace buflog
