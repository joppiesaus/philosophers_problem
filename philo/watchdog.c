/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   watchdog.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:40:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/25 17:36:25 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <unistd.h> /* usleep */

// IDEA: this is the only thing that gets pthread_join'd.
// Then if it exits, the main also exits.
// TODO: should mutex_lock be protected?

/* it doesn't matter that the last_mal_mutex is still locked when the
 * philosopher dies, as death means the program should terminate anyways. */
static int	check_death(t_thinker *thinker)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&thinker->last_meal_mutex);
	if (thinker->last_meal_timestamp + (uint64_t)thinker->vars->time_to_die
		< get_time_since_start(thinker->vars))
	{
		starve(thinker);
		status = 1;
	}
	pthread_mutex_unlock(&thinker->last_meal_mutex);
	return (status);
}

static int	check_max_meals(t_thinker *thinker)
{
	int	status;

	pthread_mutex_lock(&thinker->meals_eaten_mutex);
	status = (thinker->meals_eaten >= thinker->vars->max_meals);
	pthread_mutex_unlock(&thinker->meals_eaten_mutex);
	return (status);
}

static int	process(const t_table *table)
{
	uint32_t	i;

	i = 0;
	while (i < table->population)
	{
		if (check_death(&table->guests[i]))
			return (1);
		i++;
	}
	if (table->vars->is_max_meals_enabled)
	{
		i = 0;
		while (i < table->population)
		{
			if (!check_max_meals(&table->guests[i]))
				break ;
			i++;
		}
		if (i == table->population)
			return (1);
	}
	return (0);
}

/* this is a thread which checks if the simulation should stop. */
// TODO: determine sleep time usleep
void	*watchdog_routine(void *arg)
{
	t_table		*table;

	table = (t_table *)arg;
	msleep(min(table->vars->time_to_eat, table->vars->time_to_die) / 2);
	while (1)
	{
		if (process(table))
		{
			break ;
		}
		usleep(16);
	}
	pthread_mutex_lock(&table->should_stop_mutex);
	table->should_stop = 1;
	pthread_mutex_unlock(&table->should_stop_mutex);
	return (NULL);
}
