/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   watchdog.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:40:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/05 12:46:33 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <unistd.h> /* usleep */

/* my earlier approach was the watchdog would just return on simulation end,
 * and only have the simulation thread join'ed. That way, the program would just
 * exit. However, it didn't work, as sometimes it would just print garbage data
 * from the old threads even if the main process already seemed to exit. */

/* Somewhat confusingly, the set_stop_flag is set here already.
 * We set it before the unlock of the stdout_mutex. This means that when
 * a thinker receives access to the stdout, it will then check if the stop
 * flag is set. If we wouldn't set the stop flag here there would be a race
 * condition and it might be that a thinker just spews out the message even if
 * the simulation is already halted.
 */
static int	check_death(t_thinker *thinker)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&thinker->last_meal_mutex);
	pthread_mutex_lock(&thinker->vars->table->stdout_mutex);
	if (thinker->last_meal_timestamp + (uint64_t)thinker->vars->time_to_die
		< get_time_since_start(thinker->vars))
	{
		set_stop_flag(thinker->vars->table);
		starve(thinker);
		status = 1;
	}
	pthread_mutex_unlock(&thinker->vars->table->stdout_mutex);
	pthread_mutex_unlock(&thinker->last_meal_mutex);
	return (status);
}

static int	check_max_meals(t_thinker *thinker)
{
	int	status;

	pthread_mutex_lock(&thinker->vars->table->stdout_mutex);
	pthread_mutex_lock(&thinker->meals_eaten_mutex);
	status = (thinker->meals_eaten >= thinker->vars->max_meals);
	pthread_mutex_unlock(&thinker->meals_eaten_mutex);
	pthread_mutex_unlock(&thinker->vars->table->stdout_mutex);
	return (status);
}

/* returns 1 if the simulation should stop, 0 on continue. */
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

/* this is a thread which checks if the simulation should stop.
 * the reason why we return a fork when population == 1 is because
 * it will otherwise forever hang in an attempt to take the right fork
 * (the same fork). */
void	*watchdog_routine(void *arg)
{
	t_table		*table;

	table = (t_table *)arg;
	msleep(min(table->vars->time_to_eat, table->vars->time_to_die));
	while (1)
	{
		if (process(table))
		{
			break ;
		}
		usleep(128);
		usleep(128);
		usleep(128);
		usleep(128);
		usleep(128);
		usleep(128);
	}
	set_stop_flag(table);
	if (table->population == 1)
	{
		return_fork(table->guests[0].left_fork);
	}
	return (NULL);
}
