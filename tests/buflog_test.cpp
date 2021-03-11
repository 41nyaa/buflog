#include <cstring>
#include <string>
#include <stdio.h>
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
    logger.Flush();
    char buf1[] = {"abcdefghijklmno\n\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"};

    std::ifstream file(filename.c_str(), std::ios::in|std::ios::binary);
    char* contents = nullptr;
    ASSERT_EQ(true, file.is_open());
    file.seekg(0, std::ios_base::end);
    int size = file.tellg();
    contents = new char[size];
    memset(contents, 0x0, size);
    file.seekg (0, std::ios::beg);
    file.read (contents, size);
    file.close();
    perror(contents);

    EXPECT_EQ(strlen(buf1), size);
    EXPECT_EQ(0, std::memcmp(contents, buf1, bufsize));
    delete[] contents;
}
}  // buflogtest
