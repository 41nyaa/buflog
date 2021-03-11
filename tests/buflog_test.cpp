#include <cstring>
#include <string>
#include <iostream>
#include <fstream>

#include "gtest/gtest.h"
#include "buflog.h"

namespace buflogtest {

class BufLogTest : public ::testing::Test {
 public:

    BufLogTest() {
    }

 protected:
     void SetUp() override { 
    }

    void TearDown() override {
    }
 };

TEST_F(BufLogTest, Flush) {
    std::string filename("./buflog_test.log");
    const int bufsize = 32;

    buflog::Logger logger(filename, bufsize);
    std::string log1("abcdefghijklmno\n");  //16 characters
    logger.Log(log1);
    EXPECT_EQ(0, logger.Flush());
    char buf1[] = {"abcdefghijklmno\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"};

    std::ifstream file1(filename.c_str(), std::ios::in|std::ios::binary);
    char* contents1 = nullptr;
    ASSERT_EQ(true, file1.is_open());
    file1.seekg(0, std::ios_base::end);
    int size = file1.tellg();
    contents1 = new char[size];
    memset(contents1, 0x0, size);
    file1.seekg (0, std::ios::beg);
    file1.read (contents1, size);
    file1.close();

    EXPECT_EQ(strlen(buf1), size);
    EXPECT_EQ(0, std::memcmp(contents1, buf1, size));
    delete[] contents1;

    std::string log2("pqrstuvwxyz1234\n");  //16 characters
    logger.Log(log2);
    EXPECT_EQ(0, logger.Flush());
    char buf2[] = {"abcdefghijklmno\npqrstuvwxyz1234\n"};

    std::ifstream file2(filename.c_str(), std::ios::in|std::ios::binary);
    char* contents2 = nullptr;
    ASSERT_EQ(true, file2.is_open());
    file2.seekg(0, std::ios_base::end);
    size = file2.tellg();
    contents2 = new char[size];
    memset(contents2, 0x0, size);
    file2.seekg (0, std::ios::beg);
    file2.read (contents2, size);
    file2.close();

    EXPECT_EQ(bufsize, size);
    EXPECT_EQ(0, std::memcmp(contents2, buf2, size));
    delete[] contents2;
}
}  // buflogtest
