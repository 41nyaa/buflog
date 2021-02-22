
/*
 * Copyright (c) 2021 41nya
 * All rights reserved.
 */
#include "sharedbuffer.h"

#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstring>

#include "errorutil.h"

namespace buflog {

SharedBuffer::SharedBuffer(const std::string name, const int size)
        : shmid(0)
        , shmaddr(NULL)
        , bufsize(size)
        , errstr("") {
    key_t key = ftok(name.c_str(), 1);
    if (-1 == key) {
        ToErrStr(&errstr, __func__, errno);
        return;
    }

    shmid = shmget(key, size, IPC_CREAT);
    if (-1 == shmid) {
        ToErrStr(&errstr, __func__, errno);
        return;
    }

    shmaddr = shmat(shmid, NULL, 0);
    if (NULL == shmaddr) {
        ToErrStr(&errstr, __func__, errno);
        return;
    }

    memset(shmaddr, 0x0, size);
}

SharedBuffer::~SharedBuffer() {
    shmdt(shmaddr);
    if (-1 == shmctl(shmid, IPC_RMID, NULL)) {
        ToErrStr(&errstr, __func__, errno);
        return;
    }
}

void SharedBuffer::Write(std::string msg) {
    char* msgptr = const_cast<char*>(msg.c_str());
    int  msgsize = msg.size();
    int  remain = writeaddr + msg.size() - (bufsize - 1);
    if (remain > 0) {
        memcpy(reinterpret_cast<void*>(writeaddr), msgptr, msgsize - remain);
        msgptr += msgsize - remain;

        memcpy(shmaddr, msgptr, remain);
        writeaddr = reinterpret_cast<uint64_t>(shmaddr) + remain;
    } else {
        memcpy(reinterpret_cast<void*>(writeaddr), msgptr, msgsize);
        writeaddr += msgsize;
    }
}
}  /// namespace buflog
