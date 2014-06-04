#include <gtest\gtest.h>

TEST(my_arbitary_category_name, my_arbitrary_test_name)
{
   int i = 7;
   int j = 10;
   int kyeboard_mash_akdhfjad = i * j;

   // notice how both these tests run (and how both fail independently)
   //EXPECT_EQ(60, kyeboard_mash_akdhfjad);
   //EXPECT_TRUE(90 == kyeboard_mash_akdhfjad);
   EXPECT_EQ(70, kyeboard_mash_akdhfjad);
   EXPECT_TRUE(70 == kyeboard_mash_akdhfjad);
}

TEST(my_arbitrary_catagory_name, some_other_test)
{
   int number = 2;
   EXPECT_FALSE(1 == number);
}