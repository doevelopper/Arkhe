#include <arkhe/osgi/core/BackTraceTest.hpp>

using osgi::core::test::BackTraceTest;

BackTraceTest::BackTraceTest()
	: objectToTest()
{

}

BackTraceTest::~BackTraceTest()
{

}

void BackTraceTest::SetUp ()
{
    objectToTest = new BackTrace();
}

void BackTraceTest::TearDown ()
{
    delete objectToTest;
}

TEST_F(BackTraceTest , testStackSize)
{
	EXPECT_TRUE(!objectToTest->stackFrame(1).contains("BackTrace"));
}

TEST_F(BackTraceTest , testReturnAddress)
{
}

TEST_F(BackTraceTest , testStackTrace)
{
}
