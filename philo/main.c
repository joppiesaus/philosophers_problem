/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:55:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/13 12:52:42 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <stdlib.h> /* malloc */

/* inits the guests philosophers at the table, depends on forks. */
t_thinker	*init_guests(t_table *table)
{
	t_thinker	*guests;
	uint32_t	i;

	guests = malloc(sizeof(t_thinker) * table->population);
	if (guests)
	{
		i = 0;
		while (i < table->population)
		{
			guests[i].left_fork = &table->forks[i];
			guests[i].right_fork = &table->forks[(i + 1) % table->population];
			guests[i].number = i + 1;
			guests[i].vars = table->vars;
			i++;
		}
	}
	return (guests);
}

/* initializes a table with philosophers and forks.
 * no threading yet. Returns 1 on success, 0 on malloc fail. */
int	init_table(t_table *table)
{
	table->forks = init_forks(table->population);
	if (!table->forks)
		return (0);
	table->guests = init_guests(table);
	if (!table->guests)
		return (0);
	return (init_threads(table));
}

int	init_threads(t_table *table)
{
	uint32_t	i;

	table->vars->start_timestamp = get_time();
	i = 0;
	while (i < table->population)
	{
		if (pthread_create(&table->guests[i].thread, NULL,
				&thinker_start_routine, (void *)&table->guests[i]) == -1)
			return (0);
		i++;
	}
	i = 0;
	while (i < table->population)
	{
		if (pthread_join(table->guests[i].thread, NULL) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_table	table;

	table.vars = &vars;
	if (!parse_args(argc, argv, &table))
	{
		return (1);
	}
	else if (!init_table(&table))
	{
		return (1);
	}
	return (0);
}
