/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_watchdog.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 17:40:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/05 12:47:34 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <unistd.h> /* usleep */

/* we do not unlock the stdout semaphore on death, so that everyone thinker
 * just waits until they are killed by the killer. */
static int	check_death(t_thinker *thinker)
{
	int	status;

	status = 0;
	sem_wait(thinker->last_meal_sem);
	sem_wait(thinker->vars->table->stdout_sem);
	if (thinker->last_meal_timestamp + (uint64_t)thinker->vars->time_to_die
		< get_time_since_start(thinker->vars))
	{
		set_stop_flag(thinker->vars->table);
		sem_post(thinker->vars->table->killer_sem);
		starve(thinker);
		status = 1;
	}
	else
	{
		sem_post(thinker->vars->table->stdout_sem);
	}
	sem_post(thinker->last_meal_sem);
	return (status);
}

void	*watchdog_routine(void *arg)
{
	t_table		*table;

	table = (t_table *)arg;
	msleep(min(table->vars->time_to_eat, table->vars->time_to_die));
	while (1)
	{
		if (check_death(table->thinker))
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
	return (NULL);
}
