#include "unity_fixture.h"

#include "util.h"

TEST_GROUP(Misc);

TEST_SETUP(Misc)
{

}

TEST_TEAR_DOWN(Misc)
{
	
}

TEST(Misc, MinMin)
{
	uint32_t	a = 4;
	uint32_t	b = 5;

	TEST_ASSERT_EQUAL_UINT32(4, min(a, b));
	TEST_ASSERT_EQUAL_UINT32(4, min(b, a));
}

TEST(Misc, MinEq)
{
	uint32_t	a = 44;
	uint32_t	b = 44;

	TEST_ASSERT_EQUAL_UINT32(44, min(a, b));
	TEST_ASSERT_EQUAL_UINT32(44, min(b, a));
}

TEST(Misc, MinIntMax)
{
	uint32_t	a = (uint32_t)0xffffffff;
	uint32_t	b = 9;

	TEST_ASSERT_EQUAL_UINT32(9, min(a, b));
	TEST_ASSERT_EQUAL_UINT32(9, min(b, a));
}

TEST_GROUP_RUNNER(Misc)
{
	RUN_TEST_CASE(Misc, MinMin);
	RUN_TEST_CASE(Misc, MinEq);
	RUN_TEST_CASE(Misc, MinIntMax);
}
