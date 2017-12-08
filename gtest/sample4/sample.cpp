#include <gtest/gtest.h>
#include "fun.h"

//Sample 4: another basic example of using Google Test  
// Tests the Increment() method.  
TEST(Counter, Increment) {  
    Counter c;  
  
    // EXPECT_EQ() evaluates its arguments exactly once, so they  
    // can have side effects.  
  
    EXPECT_EQ(0, c.Increment());  
    EXPECT_EQ(1, c.Increment());  
    EXPECT_EQ(2, c.Increment());  
}  

int main (int argc, char* argv[])  
{  
    testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS();  
  
    return 0;  
}  
  
