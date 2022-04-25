/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 14:54:14 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/25 17:39:11 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

static void	mtake_fork(t_thinker *thinker, t_fork *fork)
{
	take_fork(fork);
	thinker_print_msg(thinker, "has taken a fork");
}

void	eat(t_thinker *thinker)
{
	mtake_fork(thinker, thinker->left_fork);
	mtake_fork(thinker, thinker->right_fork);
	thinker_print_msg(thinker, "is eating");
	msleep(thinker->vars->time_to_eat);
	pthread_mutex_lock(&thinker->last_meal_mutex);
	thinker->last_meal_timestamp = get_time_since_start(thinker->vars);
	pthread_mutex_unlock(&thinker->last_meal_mutex);
	return_fork(thinker->left_fork);
	thinker_print_msg(thinker, "has put the  left fork back on the table");
	return_fork(thinker->right_fork);
	thinker_print_msg(thinker, "has put the right fork back on the table");
	pthread_mutex_lock(&thinker->meals_eaten_mutex);
	thinker->meals_eaten++;
	pthread_mutex_unlock(&thinker->meals_eaten_mutex);
}

void	think(t_thinker *thinker)
{
	thinker_print_msg(thinker, "is thinking");
}

void	thinker_sleep(t_thinker *thinker)
{
	thinker_print_msg(thinker, "is sleeping");
	msleep(thinker->vars->time_to_sleep);
}

void	starve(t_thinker *thinker)
{
	thinker_print_msg(thinker, "haz died :(");
}
