#include "unity_fixture.h"

#include "phil.h"

int	is_correct_number_str(const char *str);
int	atoui(const char *str, uint32_t *ref);
int	parse_args(int argc, char **argv, t_table *table);

TEST_GROUP(Parser);

TEST_SETUP(Parser)
{

}

TEST_TEAR_DOWN(Parser)
{
	
}

TEST(Parser, NumberArg)
{
	TEST_ASSERT_EQUAL_INT(1, is_correct_number_str("0"));
	TEST_ASSERT_EQUAL_INT(1, is_correct_number_str("0234689"));
	TEST_ASSERT_EQUAL_INT(0, is_correct_number_str("-1"));
	TEST_ASSERT_EQUAL_INT(0, is_correct_number_str(""));
	TEST_ASSERT_EQUAL_INT(0, is_correct_number_str("fjlsfjk"));
	TEST_ASSERT_EQUAL_INT(0, is_correct_number_str("234248alsdkfjlsfjk"));
}

TEST(Parser, Atoui)
{
	uint32_t	n;

	n = 23456789;
	TEST_ASSERT_EQUAL_INT(1, atoui("0", &n));
	TEST_ASSERT_EQUAL_UINT32(0, n);
	TEST_ASSERT_EQUAL_INT(1, atoui("9", &n));
	TEST_ASSERT_EQUAL_UINT32(9, n);
	TEST_ASSERT_EQUAL_INT(1, atoui("4294967295", &n));
	TEST_ASSERT_EQUAL_UINT32((uint32_t)4294967295, n);
	TEST_ASSERT_EQUAL_INT(1, atoui("4294967295", &n));
	n = 0xfa1afe1;
	TEST_ASSERT_EQUAL_INT(0, atoui("4294967296", &n));
	TEST_ASSERT_EQUAL_UINT32(0xfa1afe1, n);
	TEST_ASSERT_EQUAL_INT(0, atoui("42949234294810294801298409281340982490283467296", &n));
	TEST_ASSERT_EQUAL_UINT32(0xfa1afe1, n);
}

TEST(Parser, ParseArgs5)
{
	t_vars	vars;
	t_table	table;

	table.vars = &vars;
	char	*args[] = { "phil", "100", "100", "100", "100" };

	TEST_ASSERT_EQUAL_INT(1, parse_args(5, args, &table));
	TEST_ASSERT_EQUAL_UINT32(100, table.population);
	TEST_ASSERT_EQUAL_UINT32(100, table.vars->time_to_die);
	TEST_ASSERT_EQUAL_UINT32(100, table.vars->time_to_eat);
	TEST_ASSERT_EQUAL_UINT32(100, table.vars->time_to_sleep);
	TEST_ASSERT_EQUAL_INT64(-1, table.vars->max_meals);
}

TEST(Parser, ParseArgs6)
{
	t_vars	vars;
	t_table	table;

	table.vars = &vars;
	char	*args[] = { "phil", "4294967295", "100", "100", "100", "4294967295" };

	TEST_ASSERT_EQUAL_INT(1, parse_args(6, args, &table));
	TEST_ASSERT_EQUAL_UINT32(4294967295, table.population);
	TEST_ASSERT_EQUAL_UINT32(100, table.vars->time_to_die);
	TEST_ASSERT_EQUAL_UINT32(100, table.vars->time_to_eat);
	TEST_ASSERT_EQUAL_UINT32(100, table.vars->time_to_sleep);
	TEST_ASSERT_EQUAL_INT64(4294967295, table.vars->max_meals);
}

TEST(Parser, ParseArgsShouldFail)
{
	t_vars	vars;
	t_table	table;

	table.vars = &vars;
	char	*args[] = { "phil", "4294967296", "100", "100", "100", "4294967295" };
	char	*args2[] = { "phil", "42944", "100", "4967295" };

	TEST_ASSERT_EQUAL_INT(0, parse_args(6, args, &table));
	TEST_ASSERT_EQUAL_INT(0, parse_args(4, args2, &table));
}

TEST_GROUP_RUNNER(Parser)
{
	RUN_TEST_CASE(Parser, NumberArg);
	RUN_TEST_CASE(Parser, Atoui);
	RUN_TEST_CASE(Parser, ParseArgs5);
	RUN_TEST_CASE(Parser, ParseArgs6);
	RUN_TEST_CASE(Parser, ParseArgsShouldFail);
}
