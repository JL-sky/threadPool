#include "safequeue.h"
#include <gtest/gtest.h>
#include <string>

#if 0
int add(const int &a, const int &b) { return a + b; }

TEST(testcase1, AddTest) { EXPECT_EQ(add(1, 2), 4); }

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif

#if 0
std::vector<int> x = {1, 2, 3, 4};
std::vector<int> y = {1, 2, 4, 4};

TEST(VectorTest, demo) {
    for (int i = 0; i < x.size(); ++i) {
        EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
    }
}
#endif

#if 0
int Foo(int a, int b) {
    if (a == 0 || b == 0) {
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return b;
    return Foo(b, c);
}

TEST(FooTest, HandleZeroInput) {
    EXPECT_ANY_THROW(Foo(10, 0));
    EXPECT_THROW(Foo(0, 5), char *);
}
#endif

#if 0
class QueueTest : public testing::Test {
 protected:
    QueueTest() {
        q1_.Enqueue(1);
        q2_.Enqueue(2);
        q2_.Enqueue(3);
    }

    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
};

TEST_F(QueueTest, IsEmptyInitially) { EXPECT_EQ(q0_.size(), 0); }

TEST_F(QueueTest, DequeueWorks) {
    try {
        int n = q0_.Dequeue();
        FAIL() << "Expected exception for empty queue";
    } catch (const std::runtime_error &e) {
        EXPECT_STREQ(e.what(), "Queue is empty");
    }

    int n = q1_.Dequeue();
    EXPECT_EQ(n, 1);
    EXPECT_EQ(q1_.size(), 0);

    n = q2_.Dequeue();
    EXPECT_EQ(n, 2);
    EXPECT_EQ(q2_.size(), 1);

    n = q2_.Dequeue();
    EXPECT_EQ(n, 3);
    EXPECT_EQ(q2_.size(), 0);
}
#endif

#if 1
// 假设我们有一个全局资源
class GlobalResource {
 public:
    GlobalResource() { std::cout << "GlobalResource Initialized" << std::endl; }

    ~GlobalResource() { std::cout << "GlobalResource Cleaned up" << std::endl; }

    void DoSomething() {
        std::cout << "GlobalResource Doing something" << std::endl;
    }
};

// 创建一个全局资源实例
GlobalResource global_resource;

// 在整个测试套件运行前执行初始化
class GlobalTestSuite : public ::testing::Test {
 public:
    static void SetUpTestSuite() {
        // 在所有测试开始之前执行一次
        std::cout << "GlobalTestSuite SetUpTestSuite()" << std::endl;
    }

    static void TearDownTestSuite() {
        // 在所有测试结束之后执行一次
        std::cout << "GlobalTestSuite TearDownTestSuite()" << std::endl;
    }

    void SetUp() override {
        // 每个测试前执行
        std::cout << "GlobalTestSuite SetUp()" << std::endl;
    }

    void TearDown() override {
        // 每个测试后执行
        std::cout << "GlobalTestSuite TearDown()" << std::endl;
    }
};
// 测试1
TEST_F(GlobalTestSuite, Test1) {
    std::cout << "Running Test1" << std::endl;
    global_resource.DoSomething(); // 使用全局资源
    ASSERT_TRUE(true);
}

// 测试2
TEST_F(GlobalTestSuite, Test2) {
    std::cout << "Running Test2" << std::endl;
    global_resource.DoSomething(); // 使用全局资源
    ASSERT_TRUE(true);
}

#endif

#if 1
int main(int argc, char **argv) {
    // testing::AddGlobalTestEnvironment(new FooEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif