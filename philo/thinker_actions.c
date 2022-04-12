/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker_actions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 14:54:14 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/12 15:53:22 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

void	eat(t_thinker *thinker)
{
	// todo: eat
	thinker_print_msg(thinker, "is eating");
	msleep(thinker->vars->time_to_eat);
	thinker->last_meal_timestamp = get_time_since_start(thinker->vars);
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
