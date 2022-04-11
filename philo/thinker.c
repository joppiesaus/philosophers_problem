/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thinker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:30:57 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/11 14:44:32 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

#include <unistd.h> /* write */

void	*thinker_start_routine(void *arg)
{
	return (NULL);
}

void	*thinker_print_msg(t_thinker *thinker, void *msg)
{
	char	dst[256];
	size_t	i;

	i = 0;
	// todo: timestamp
	writer_wr_char(dst, &i, ' ');
	writer_wr_uint(dst, &i, thinker->number);
	writer_wr_char(dst, &i, ' ');
	writer_wr_str(dst, &i, msg);
	if (write(1, dst, i) == -1)
	{
		// TODO: fail
	}
}
