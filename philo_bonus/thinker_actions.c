/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1584/07/10 13:30:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:42:15 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <unistd.h> /* write */

/* takes a fork and prints a message. if it sees that the simulation has
 * ended, returns the fork. Also, quite sad return fork doesn't have a
 * message. */
static int	mtake_fork(t_thinker *thinker)
{
	take_fork(thinker);
	if (!thinker_print_msg(thinker, "has taken a fork"))
	{
		return_fork(thinker);
		return (0);
	}
	return (1);
}

/* no need to return the forks on error, because it will hang until the
 * child thinker is killed anyways */
int	eat(t_thinker *thinker)
{
	if (!mtake_fork(thinker)
		|| !mtake_fork(thinker)
		|| !thinker_print_msg(thinker, "is eating")
		|| !msleep_deathcheck(thinker->vars->table,
			thinker->vars->time_to_eat))
	{
		return (0);
	}
	sem_wait(thinker->last_meal_sem);
	thinker->last_meal_timestamp = get_time_since_start(thinker->vars);
	sem_post(thinker->last_meal_sem);
	return_fork(thinker);
	return_fork(thinker);
	thinker->meals_eaten++;
	if (thinker->vars->is_max_meals_enabled
		&& thinker->meals_eaten >= thinker->vars->max_meals)
	{
		sem_post(thinker->vars->table->thinkers_finished_sem);
		thinker->vars->is_max_meals_enabled = 0;
	}
	return (1);
}

int	think(t_thinker *thinker)
{
	return (thinker_print_msg(thinker, "is thinking"));
}

int	thinker_sleep(t_thinker *thinker)
{
	return (thinker_print_msg(thinker, "is sleeping")
		&& msleep_deathcheck(thinker->vars->table,
			thinker->vars->time_to_sleep));
}

#define REDBOLD "\x1B[1;37;41m"
#define RESET "\x1B[0m"

void	starve(t_thinker *thinker)
{
	char	buf[WRITER_BUF_LEN];
	size_t	i;

	thinker_write_to_str(thinker, buf, &i, REDBOLD "died" RESET);
	write(1, buf, i);
}
