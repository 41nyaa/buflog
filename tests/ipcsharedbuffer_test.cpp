#include <cstring>
#include <string>

#include "gtest/gtest.h"
#include "ipcsharedbuffer.h"

namespace buflogtest {

const int bufsize = 32;
class IPCSharedBufferTest : public ::testing::Test {
 public:
    buflog::IPCSharedBuffer buf;

    IPCSharedBufferTest() : buf(std::string("."), bufsize){
    }

    void* GetShmAddr() {
        return buf.shmaddr;
    }

 protected:
     void SetUp() override { 
    }

    void TearDown() override {
    }
 };

TEST_F(IPCSharedBufferTest, Write) {
    void* shmaddr = GetShmAddr();
    std::string log1("abcdefghijklmno\n");  //16 characters
    buf.Write(log1);
    char buf1[] = {"abcdefghijklmno\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"};
    EXPECT_EQ(0, std::memcmp(shmaddr, buf1, bufsize));

    std::string log2("pqrstuvwxyz1234\n");  //16 characters
    buf.Write(log2);
    char buf2[] = {"abcdefghijklmno\npqrstuvwxyz1234\n"};
    EXPECT_EQ(0, std::memcmp(shmaddr, buf2, bufsize));

    std::string log3("5678901234\n");  // 11 characters
    buf.Write(log3);          
    char buf3[] = {"5678901234\nlmno\npqrstuvwxyz1234\n"};
    EXPECT_EQ(0, std::memcmp(shmaddr, buf3, bufsize));

    std::string log4("abcdefghijklmnopqrstu\n"); // 22 characters
    buf.Write(log4);          
    char buf4[] = {"\n678901234\nabcdefghijklmnopqrstu"};
    EXPECT_EQ(0, std::memcmp(shmaddr, buf4, bufsize));
};

TEST_F(IPCSharedBufferTest, Copy) {
    std::string log1("abcdefghijklmno\n");  //16 characters
    buf.Write(log1);
    const char buf1[] = {"abcdefghijklmno\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"};
    std::vector<char> cpbuf1;
    buf.Copy(cpbuf1);
    EXPECT_EQ(0, std::memcmp(&cpbuf1[0], buf1, bufsize));

    std::string log2("pqrstuvwxyz1234\n");  //16 characters
    buf.Write(log2);
    char buf2[] = {"abcdefghijklmno\npqrstuvwxyz1234\n"};
    std::vector<char> cpbuf2;
    buf.Copy(cpbuf2);
    EXPECT_EQ(0, std::memcmp(&cpbuf2[0], buf2, bufsize));

    std::string log3("5678901234\n");  // 11 characters
    buf.Write(log3);          
    char buf3[] = {"lmno\npqrstuvwxyz1234\n5678901234\n"};
    std::vector<char> cpbuf3;
    buf.Copy(cpbuf3);
    EXPECT_EQ(0, std::memcmp(&cpbuf3[0], buf3, bufsize));

    std::string log4("abcdefghijklmnopqrstu\n"); // 22 characters
    buf.Write(log4);          
    char buf4[] = {"678901234\nabcdefghijklmnopqrstu\n"};
    std::vector<char> cpbuf4;
    buf.Copy(cpbuf4);
    EXPECT_EQ(0, std::memcmp(&cpbuf4[0], buf4, bufsize));
}
}  // buflogtest
