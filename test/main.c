#include "unity_fixture.h"

/* Which test groups to run */
static void	run_all_tests(void)
{
	RUN_TEST_GROUP(Writer);
	RUN_TEST_GROUP(Parser);
	RUN_TEST_GROUP(Misc);
}

int	main(int argc, const char *argv[])
{
	return (UnityMain(argc, argv, run_all_tests));
}
