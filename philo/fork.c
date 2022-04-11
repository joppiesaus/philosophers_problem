/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:03:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/11 13:09:02 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

#include <stdlib.h> /* malloc, free */

void	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
}

void	return_fork(t_fork *fork)
{
	pthread_mutex_unlock(&fork->mutex);
}

static int	init_fork(t_fork *fork)
{
	return (pthread_mutex_init(&fork->mutex, NULL) != -1);
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
			if (!init_fork(&forks[i]))
			{
				free(forks);
				return (NULL);
			}
			i++;
		}
	}
	return (forks);
}
