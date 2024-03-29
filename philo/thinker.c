/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:30:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/06 13:16:07 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <unistd.h> /* write */

void	*thinker_start_routine(void *arg)
{
	t_thinker	*thinker;

	thinker = (t_thinker *)arg;
	pthread_mutex_lock(&thinker->last_meal_mutex);
	thinker->last_meal_timestamp = get_time_since_start(thinker->vars);
	pthread_mutex_unlock(&thinker->last_meal_mutex);
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
	return (NULL);
}

/* writes a message, checking locks as well. */
int	thinker_print_msg(t_thinker *thinker, const char *msg)
{
	char	dst[WRITER_BUF_LEN];
	size_t	i;

	pthread_mutex_lock(&thinker->vars->table->stdout_mutex);
	thinker_write_to_str(thinker, dst, &i, msg);
	if (should_stop_simulation(thinker->vars->table))
	{
		pthread_mutex_unlock(&thinker->vars->table->stdout_mutex);
		return (0);
	}
	else if (write(1, dst, i) == -1)
	{
		set_stop_flag(thinker->vars->table);
		pthread_mutex_unlock(&thinker->vars->table->stdout_mutex);
		return (0);
	}
	pthread_mutex_unlock(&thinker->vars->table->stdout_mutex);
	return (1);
}

/* just writes a message in the <timestamp> <philosopher> <message> format,
 * to a buffer(not to stdout). */
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
