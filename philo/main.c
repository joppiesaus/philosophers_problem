/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:55:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/08 16:43:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

#include <stdlib.h> /* malloc */

t_philosopher	*init_guests(uint32_t amount)
{
	t_philosopher	*guests;
	uint32_t		i;

	guests = malloc(sizeof(t_philosopher) * amount);
	if (guests)
	{
		i = 0;
		while (i < amount)
		{
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
	table->guests = init_guests(population);
	if (!table->guests)
		return (0);
	table->forks = init_forks(population);
	if (!table->forks)
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
