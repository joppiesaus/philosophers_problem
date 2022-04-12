/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:30:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/12 14:36:09 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"
#include "util.h"

#include <unistd.h> /* write */

void	*thinker_start_routine(void *arg)
{
	t_thinker	*thinker;

	thinker = (t_thinker *)arg;
	return (NULL);
}

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
	if (write(1, dst, i) == -1)
	{
		// TODO: fail
	}
}
