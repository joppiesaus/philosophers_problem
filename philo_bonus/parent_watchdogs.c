/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_watchdogs.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/29 18:31:19 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:51:20 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <signal.h> /* kill */

void	*thinkers_finished_routine(void *arg)
{
	t_table		*table;
	uint32_t	n;

	table = (void *)arg;
	n = 0;
	while (n < table->population)
	{
		if (sem_wait(table->thinkers_finished_sem) == -1)
			ft_putstr_fd(2, "sem_wait finished_routine failed\n");
		n++;
	}
	sem_post(table->killer_sem);
	return (NULL);
}

void	*killer_routine(void *arg)
{
	t_table		*table;
	uint32_t	i;

	i = 0;
	table = (t_table *)arg;
	if (sem_wait(table->killer_sem) == -1)
		ft_putstr_fd(2, "sem_wait killer failed\n");
	set_stop_flag(table);
	sem_wait(table->pids_sem);
	while (i < table->population)
	{
		kill(table->child_pids[i], SIGKILL);
		table->child_pids[i] = -1;
		i++;
	}
	sem_post(table->pids_sem);
	return (NULL);
}
