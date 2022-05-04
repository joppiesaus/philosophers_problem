/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:03:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/28 17:37:15 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	take_fork(t_thinker *thinker)
{
	sem_wait(thinker->vars->table->fork_sem);
}

void	return_fork(t_thinker *thinker)
{
	sem_post(thinker->vars->table->fork_sem);
}
