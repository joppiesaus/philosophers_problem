/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:55:03 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/05 12:54:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <stdlib.h> /* malloc, exit */
#include <unistd.h> /* write */

#include <sys/wait.h> /* wait */
#include <signal.h> /* signal */

/* doubly waiting for stdout_sem is so that the client forever hangs until
 * it's killed, plus nobody can say anything */
static pid_t	do_fork(t_table *table)
{
	pid_t		pid;
	t_vars		vars;
	t_thinker	thinker;

	vars = *table->vars;
	thinker = *table->thinker;
	pid = fork();
	if (pid == -1)
		pexit("fork failed\n");
	else if (pid == 0)
	{
		table->vars = &vars;
		vars.table = table;
		table->thinker = &thinker;
		if (thinker_start_routine(table) == 0)
		{
			exit(0);
		}
		sem_post(table->killer_sem);
		sem_wait(table->stdout_sem);
		sem_wait(table->stdout_sem);
	}
	return (pid);
}

static void	init_forks(t_table *table)
{
	pid_t		pid;
	uint32_t	i;

	i = 0;
	sem_wait(table->pids_sem);
	table->child_pids = malloc(table->population * sizeof(pid_t));
	if (table->child_pids == NULL)
		pexit("malloc failure\n");
	table->vars->start_timestamp = get_time();
	while (i < table->population)
	{
		table->thinker->number = i + 1;
		pid = do_fork(table);
		if (pid == 0)
		{
			break ;
		}
		table->child_pids[i] = pid;
		i++;
	}
	sem_post(table->pids_sem);
}

/* waits for the children/thinkers to finish, kills the rest on exit.
 * it is protected by a semaphore so that the killer thread doesn't
 * kill things twice or something/data race. */
static void	wait_for_childs(t_table *table)
{
	int			status;
	pid_t		pid;
	uint32_t	i;

	while (1)
	{
		i = 0;
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		sem_wait(table->pids_sem);
		while (i < table->population)
		{
			if (table->child_pids[i] != -1 && pid != table->child_pids[i])
			{
				kill(pid, SIGKILL);
			}
			table->child_pids[i] = -1;
			i++;
		}
		sem_post(table->pids_sem);
	}
}

/* initializes a table with philosophers and forks.
 * no threading yet. Returns 1 on success, 0 on malloc fail. */
int	init_table(t_table *table)
{
	table->thinker->meals_eaten = 0;
	table->should_stop = 0;
	table->thinker->vars = table->vars;
	init_parent_sems(table);
	init_forks(table);
	if (pthread_create(&table->killer_thread, NULL, &killer_routine,
			(void *)table) == -1
		|| pthread_create(&table->thinkers_finished_thread, NULL,
			&thinkers_finished_routine, (void *)table))
	{
		pexit("pthread_create failed\n");
	}
	else if (pthread_detach(table->killer_thread) == -1
		|| pthread_detach(table->thinkers_finished_thread) == -1)
	{
		pexit("pthread_detach failed\n");
	}
	wait_for_childs(table);
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_table		table;
	t_thinker	thinker;

	table.thinker = &thinker;
	table.vars = &vars;
	vars.table = &table;
	if (!parse_args(argc, argv, &table))
	{
		return (1);
	}
	else if (!init_table(&table))
	{
		pexit("malloc, semaphore or fork fail\n");
		return (1);
	}
	return (0);
}
