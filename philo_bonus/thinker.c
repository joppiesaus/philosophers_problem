/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:30:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:38:27 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <unistd.h> /* write */

static int	init_thinker(t_thinker *thinker)
{
	if (!init_child_sems(thinker))
	{
		return (0);
	}
	sem_wait(thinker->last_meal_sem);
	thinker->last_meal_timestamp = get_time_since_start(thinker->vars);
	sem_post(thinker->last_meal_sem);
	if (pthread_create(&thinker->watchdog_thread, NULL, &watchdog_routine,
			(void *)thinker->vars->table) == -1)
	{
		ft_putstr_fd(2, "failed to create child watchdog thread\n");
		return (0);
	}
	return (1);
}

int	thinker_start_routine(t_table *table)
{
	t_thinker	*thinker;

	thinker = table->thinker;
	if (!init_thinker(thinker))
		return (0);
	if (thinker->number % 2 == 0)
		usleep(32);
	while (1)
	{
		if (!eat(thinker)
			|| !thinker_sleep(thinker)
			|| !think(thinker))
		{
			break ;
		}
	}
	if (pthread_join(thinker->watchdog_thread, NULL) == -1)
	{
		ft_putstr_fd(2, "failed to create child watchdog thread\n");
		return (1);
	}
	return (0);
}

int	thinker_print_msg(t_thinker *thinker, const char *msg)
{
	char	dst[WRITER_BUF_LEN];
	size_t	i;

	thinker_write_to_str(thinker, dst, &i, msg);
	sem_wait(thinker->vars->table->stdout_sem);
	if (should_stop_simulation(thinker->vars->table))
	{
		sem_post(thinker->vars->table->stdout_sem);
		return (0);
	}
	else if (write(1, dst, i) == -1)
	{
		set_stop_flag(thinker->vars->table);
		sem_post(thinker->vars->table->stdout_sem);
		return (0);
	}
	sem_post(thinker->vars->table->stdout_sem);
	return (1);
}

void	thinker_write_to_str(t_thinker *thinker, char *dst, size_t *i,
	const char *msg)
{
	*i = 0;
	writer_wr_uint(dst, i, get_time_since_start(thinker->vars));
	writer_wr_char(dst, i, ' ');
	writer_wr_uint(dst, i, thinker->number);
	writer_wr_char(dst, i, ' ');
	writer_wr_str(dst, i, msg);
	writer_wr_char(dst, i, '\n');
}
