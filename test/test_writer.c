#include "unity_fixture.h"

#include "util.h"

TEST_GROUP(Writer);

TEST_SETUP(Writer)
{

}

TEST_TEAR_DOWN(Writer)
{
	
}

TEST(Writer, WBasic)
{
	char	buf[256];
	size_t	i = 0;

	write_wr_str(buf, &i, "hello");
	buf[5] = 0;
	TEST_ASSERT_EQUAL_STRING("hello");
}

TEST_GROUP_RUNNER(Writer)
{
	RUN_TEST_CASE(WBasic);
}
