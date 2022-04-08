/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:55:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/08 17:42:38 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

#include <stdlib.h> /* malloc */

/* inits the guests philosophers at the table, depends on forks. */
t_thinker	*init_guests(t_table *table, uint32_t amount)
{
	t_thinker	*guests;
	uint32_t	i;

	guests = malloc(sizeof(t_thinker) * amount);
	if (guests)
	{
		i = 0;
		while (i < amount)
		{
			guests[i].left_fork = &table->forks[i];
			guests[i].right_fork = &table->forks[(i + 1) % amount];
			guests[i].number = i + 1;
			i++;
		}
	}
	return (guests);
}

t_fork	*init_forks(uint32_t amount)
{
	t_fork		*forks;
	uint32_t	i;

	forks = malloc(sizeof(t_fork) * amount);
	if (forks)
	{
		i = 0;
		while (i < amount)
		{
			if (pthread_mutex_init(&forks[i].mutex, NULL) == -1)
			{
				free(forks);
				return (NULL);
			}
			i++;
		}
	}
	return (forks);
}

/* initializes a table with philosophers and forks.
 * no threading yet. Returns 1 on success, 0 on malloc fail. */
int	init_table(t_table *table, uint32_t population)
{
	table->population = population;
	table->forks = init_forks(population);
	if (!table->forks)
		return (0);
	table->guests = init_guests(table, population);
	if (!table->guests)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!init_table(&table, 5))
	{
		return (1);
	}
	return (0);
}
