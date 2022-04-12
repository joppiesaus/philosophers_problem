#include "unity_fixture.h"

#include "util.h"

#include <string.h>

TEST_GROUP(Writer);

TEST_SETUP(Writer)
{

}

TEST_TEAR_DOWN(Writer)
{
	
}

TEST(Writer, WBasic)
{
	char	buf[128];
	size_t	i = 0;

	writer_wr_str(buf, &i, "hello");
	buf[5] = 0;
	TEST_ASSERT_EQUAL_STRING("hello", buf);
	TEST_ASSERT_EQUAL_size_t(5, i);
}

TEST(Writer, WAppendString)
{
	char	buf[128];
	size_t	i = 0;

	writer_wr_str(buf, &i, "hello");
	writer_wr_str(buf, &i, " world");
	buf[11] = 0;
	TEST_ASSERT_EQUAL_STRING("hello world", buf);
	TEST_ASSERT_EQUAL_size_t(11, i);
}

TEST(Writer, WCharBasic)
{
	char	buf[128];
	size_t	i = 0;

	writer_wr_char(buf, &i, 'h');
	writer_wr_char(buf, &i, 's');
	writer_wr_char(buf, &i, 'g');
	buf[3] = 0;
	TEST_ASSERT_EQUAL_STRING("hsg", buf);
	TEST_ASSERT_EQUAL_size_t(3, i);
}

TEST(Writer, WUintSingle)
{
	char	buf[2];
	size_t	i = 0;

	writer_wr_uint(buf, &i, 0);
	buf[1] = 0;
	TEST_ASSERT_EQUAL_STRING("0", buf);
	TEST_ASSERT_EQUAL_size_t(1, i);
	i = 0;
	writer_wr_uint(buf, &i, 5);
	TEST_ASSERT_EQUAL_STRING("5", buf);
	TEST_ASSERT_EQUAL_size_t(1, i);
}

TEST(Writer, WUintSimple)
{
	char	buf[32];
	size_t	i = 0;

	writer_wr_uint(buf, &i, 10);
	buf[2]= 0;
	TEST_ASSERT_EQUAL_STRING("10", buf);
}

TEST(Writer, WUintMax)
{
	char	buf[64] = { 0 };
	size_t	i = 0;

	writer_wr_uint(buf, &i, (uint64_t)-1);
	TEST_ASSERT_EQUAL_STRING("18446744073709551615", buf);
	TEST_ASSERT_EQUAL_size_t(20, i);
}

TEST(Writer, WStrOffset)
{
	char	buf[64] = { 0 };
	size_t	i = 3;

	memcpy(buf, "hello", 5);
	writer_wr_str(buf, &i, "greetings");
	TEST_ASSERT_EQUAL_STRING("helgreetings", buf);
	TEST_ASSERT_EQUAL_size_t(12, i);
}

TEST(Writer, WCombo)
{
	char	buf[64] = { 0 };
	size_t	i = 0;

	writer_wr_uint(buf, &i, 52149856);
	writer_wr_char(buf, &i, ' ');
	writer_wr_char(buf, &i, ' ');
	writer_wr_str(buf, &i, "maybe?");
	writer_wr_uint(buf, &i, 22);
	TEST_ASSERT_EQUAL_STRING("52149856  maybe?22", buf);
	TEST_ASSERT_EQUAL_size_t(18, i);
}

TEST_GROUP_RUNNER(Writer)
{
	RUN_TEST_CASE(Writer, WBasic);
	RUN_TEST_CASE(Writer, WAppendString);
	RUN_TEST_CASE(Writer, WCharBasic);
	RUN_TEST_CASE(Writer, WUintSingle);
	RUN_TEST_CASE(Writer, WUintMax);
	RUN_TEST_CASE(Writer, WStrOffset);
	RUN_TEST_CASE(Writer, WCombo);
}
