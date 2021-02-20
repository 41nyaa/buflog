#ifndef BUFLOG_INTERNAL_SHAREDBUFFER_H
#define BUFLOG_INTERNAL_SHAREDBUFFER_H

#include<string>

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
    unsigned long long writeaddr;
    std::string errstr;
};
}
#endif /* BUFLOG_INTERNAL_SHAREDBUFFER_H */
