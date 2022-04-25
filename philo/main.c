/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:55:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/25 17:39:28 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <stdlib.h> /* malloc */
#include <unistd.h> /* write */

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

	table->should_stop = 0;
	if (pthread_mutex_init(&table->should_stop_mutex, NULL) == -1)
		return (0);
	table->vars->start_timestamp = get_time();
	i = 0;
	while (i < table->population)
	{
		if (pthread_create(&table->guests[i].thread, NULL,
				&thinker_start_routine, (void *)&table->guests[i]) == -1)
			return (0);
		i++;
	}
	if (pthread_create(&table->watchdog_thread, NULL, &watchdog_routine,
			(void *)table) == -1)
	{
		return (0);
	}
	if (pthread_join(table->watchdog_thread, NULL) == -1)
	{
		return (0);
	}
	return (1);
}
/*i = 0;
	while (i < table->population)
	{
		if (pthread_join(table->guests[i].thread, NULL) == -1)
			return (0);
		i++;
	}*/

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
		write(2, "malloc or mutex init fail\n", 26);
		return (1);
	}
	return (0);
}
