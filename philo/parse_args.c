/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:56:09 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/27 14:26:35 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

/* TODO: make static on final build */
/* checks wether str is a number */
int	is_correct_number_str(const char *str)
{
	if (*str == 0)
	{
		return (0);
	}
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
		{
			return (0);
		}
		str++;
	}
	return (1);
}

/* checks amount of arguments is correct and whether every arg is a number. */
int	check_args(int argc, char **argv)
{
	int	i;

	if (!(argc == 5 || argc == 6))
	{
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_correct_number_str(argv[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

/* ascii to unsigned int. Assumes str had passed is_correct_number_str.
 * ref is set to the resulting value on success. Returns 1 on success,
 * 0 on overflow. */
int	atoui(const char *str, uint32_t *ref)
{
	uint32_t	res;
	uint32_t	prev;

	prev = 0;
	res = 0;
	while (*str)
	{
		res *= 10;
		res += *str - '0';
		if (res < prev)
		{
			return (0);
		}
		prev = res;
		str++;
	}
	*ref = res;
	return (1);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	const uint32_t	*references[] = {
		&table->population,
		&table->vars->time_to_die,
		&table->vars->time_to_eat,
		&table->vars->time_to_sleep,
		&table->vars->max_meals
	};
	int				i;

	if (!check_args(argc, argv))
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!atoui(argv[i], (uint32_t *)references[i - 1])
			|| *references[i - 1] == 0)
		{
			return (0);
		}
		i++;
	}
	table->vars->is_max_meals_enabled = (argc >= 6);
	return (1);
}
