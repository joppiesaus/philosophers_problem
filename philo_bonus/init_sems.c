/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_sems.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 14:09:07 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:37:51 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <stdlib.h> /* exit */

static int	initsem(sem_t **sem, const char *name, const uint32_t value)
{
	int	status;

	status = 1;
	*sem = sem_open(name, O_CREAT | O_EXCL, MSEMFDPERM, value);
	if (*sem == SEM_FAILED)
	{
		sem_close(*sem);
		ft_putstr_fd(2, "opening sem failed\n");
		status = 0;
	}
	else if (sem_unlink(name) == -1)
	{
		sem_close(*sem);
		ft_putstr_fd(2, "sem_unlink failed\n");
		status = 0;
	}
	return (status);
}

void	init_parent_sems(t_table *table)
{
	if (!initsem(&table->stdout_sem, MSEM_STDOUT_NAME, 1)
		|| !initsem(&table->should_stop_sem, MSEM_SHOULD_STOP_NAME, 1)
		|| !initsem(&table->thinkers_finished_sem,
			MSEM_THINKER_FINISHED_NAME, 0)
		|| !initsem(&table->fork_sem, MSEM_FORK_NAME, table->population)
		|| !initsem(&table->killer_sem, MSEM_KILLER_NAME, 0)
		|| !initsem(&table->pids_sem, MSEM_PIDS_NAME, 1))
	{
		exit(1);
	}
}

int	init_child_sems(t_thinker *thinker)
{
	return (initsem(&thinker->last_meal_sem, MSEM_LAST_MEAL_NAME, 1));
}
