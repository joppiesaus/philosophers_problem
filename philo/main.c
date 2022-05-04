/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:55:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:45:59 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <stdlib.h> /* malloc */
#include <unistd.h> /* write */

/* inits the guests philosophers at the table, depends on forks. */
static t_thinker	*init_guests(t_table *table)
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
			guests[i].meals_eaten = 0;
			if (pthread_mutex_init(&guests[i].meals_eaten_mutex, NULL) == -1
				|| pthread_mutex_init(&guests[i].last_meal_mutex, NULL) == -1)
			{
				free(guests);
				return (NULL);
			}
			i++;
		}
	}
	return (guests);
}

static int	init_threads(t_table *table)
{
	uint32_t	i;

	table->vars->start_timestamp = get_time();
	i = 0;
	while (i < table->population)
	{
		table->guests[i].last_meal_timestamp = table->vars->start_timestamp;
		if (pthread_create(&table->guests[i].thread, NULL,
				&thinker_start_routine, (void *)&table->guests[i]) == -1)
			return (0);
		i++;
	}
	if (pthread_create(&table->watchdog_thread, NULL, &watchdog_routine,
			(void *)table) == -1
		|| pthread_join(table->watchdog_thread, NULL) == -1)
		return (0);
	i = 0;
	while (i < table->population)
	{
		if (pthread_join(table->guests[i].thread, NULL) == -1)
			return (0);
		i++;
	}
	return (1);
}

/* initializes a table with philosophers and forks, then runs the threads.
 * Returns 1 on success, 0 on malloc fail. */
static int	init_table(t_table *table)
{
	table->forks = init_forks(table->population);
	if (!table->forks)
	{
		return (0);
	}
	table->guests = init_guests(table);
	if (!table->guests)
	{
		return (0);
	}
	table->should_stop = 0;
	if (pthread_mutex_init(&table->should_stop_mutex, NULL) == -1
		|| pthread_mutex_init(&table->stdout_mutex, NULL) == -1)
		return (0);
	return (init_threads(table));
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_table	table;

	table.vars = &vars;
	vars.table = &table;
	if (!parse_args(argc, argv, &table))
	{
		return (1);
	}
	else if (!init_table(&table))
	{
		write(2, "malloc, mutex or thread init fail\n", 34);
		return (1);
	}
	free(table.guests);
	free(table.forks);
	return (0);
}
