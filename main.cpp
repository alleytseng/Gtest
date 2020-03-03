#include <iostream>
using namespace std;
#include "gtest/gtest.h"
TEST(testCase,test0){
    EXPECT_EQ(5,5);
}
int main(int argc,char **argv)
{
	testing::InitGoogleTest(&argc,argv);
cout<<"hello";
RUN_ALL_TESTS();
	return 0;
}