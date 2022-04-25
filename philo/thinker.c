/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:30:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/25 17:35:48 by jobvan-d      ########   odam.nl         */
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
	if (thinker->number % 2)
		usleep(50);
	while (1)
	{
		eat(thinker);
		thinker_sleep(thinker);
		think(thinker);
	}
	return (NULL);
}

// TODO: fail when write == -1
void	thinker_print_msg(t_thinker *thinker, const char *msg)
{
	char	dst[128];
	size_t	i;

	i = 0;
	writer_wr_uint(dst, &i, get_time_since_start(thinker->vars));
	writer_wr_char(dst, &i, ' ');
	writer_wr_uint(dst, &i, thinker->number);
	writer_wr_char(dst, &i, ' ');
	writer_wr_str(dst, &i, msg);
	writer_wr_char(dst, &i, '\n');
	if (write(1, dst, i) == -1)
	{
	}
}
