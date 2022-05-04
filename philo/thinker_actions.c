/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1584/07/10 13:30:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:47:22 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <unistd.h> /* write */

/* takes a fork and prints a message. if it sees that the simulation has
 * ended, returns the fork. Also, quite sad return fork doesn't have a
 * message. */
static int	mtake_fork(t_thinker *thinker, t_fork *fork)
{
	take_fork(fork);
	if (!thinker_print_msg(thinker, "has taken a fork"))
	{
		return_fork(fork);
		return (0);
	}
	return (1);
}

int	eat(t_thinker *thinker)
{
	if (!mtake_fork(thinker, thinker->left_fork))
		return (0);
	else if (!mtake_fork(thinker, thinker->right_fork))
	{
		if (thinker->left_fork != thinker->right_fork)
			return_fork(thinker->left_fork);
		return (0);
	}
	else if (!thinker_print_msg(thinker, "is eating")
		|| !msleep_deathcheck(thinker->vars->table,
			thinker->vars->time_to_eat))
	{
		return_fork(thinker->left_fork);
		return_fork(thinker->right_fork);
		return (0);
	}
	pthread_mutex_lock(&thinker->last_meal_mutex);
	thinker->last_meal_timestamp = get_time_since_start(thinker->vars);
	pthread_mutex_unlock(&thinker->last_meal_mutex);
	return_fork(thinker->left_fork);
	return_fork(thinker->right_fork);
	pthread_mutex_lock(&thinker->meals_eaten_mutex);
	thinker->meals_eaten++;
	pthread_mutex_unlock(&thinker->meals_eaten_mutex);
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
