
#include "gtest/gtest.h"

#include "sharedbuffer.h"

class SharedBufferTest : public ::testing::Test {
 protected:
    void SetUp() { 
    }

    void TearDown() {
    }
};

TEST_F(SharedBufferTest, Constructor) {
    buflog::SharedBuffer buf(".", 128);
};
