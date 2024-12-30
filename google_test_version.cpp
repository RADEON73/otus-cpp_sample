#include "lib.h"
#include "gtest/gtest.h"

TEST(VersionTest, MoreThanZero)
{
	ASSERT_GT(version(), 0);
}