#include <iostream>

#include <gtest/gtest.h>

int add(int i, int j) {
    return i + j;
}

TEST(AddTest, IntAdd) {
    ASSERT_EQ(add(1, 2), 3)<<"Add i to 2, equals 3.";
}

TEST(AddTest, LongAdd) {
    ASSERT_EQ(add((long)1, (long)2), 4)<<"Add long 1 to long 2, euqals 4.";
}

class GlobalTest:public testing::Environment {
public:
    virtual void SetUp() {
        std::cout<<"SetUp"<<std::endl;
    }
    virtual void TearDown() {
        std::cout<<"TearDown"<<std::endl;
    }
};

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    testing::Environment* env = new GlobalTest();
    testing::AddGlobalTestEnvironment(env);

    return RUN_ALL_TESTS();
}