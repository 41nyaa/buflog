#ifndef BUFLOG_BUFLOG_H
#define BUFLOG_BUFLOG_H

#include <string>

namespace buflog {
class SharedBuffer;

class Logger {
public:
    Logger(const std::string filename, const int size);
    ~Logger();
    void Log(std::string msg);
    int Flush();

private:
    SharedBuffer* bufptr;
};
}
#endif /* BUFLOG_BUFLOG_H */
