/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 14:20:11 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/12 14:41:03 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

#include <sys/time.h>

/* returns the amount of ms since the program began. */
uint64_t	get_time_since_start(t_vars *vars)
{
	return (get_time() - vars->start_timestamp);
}

/* returns the current unix time in _mili_seconds(NOT seconds) */
uint64_t	get_time()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((uint64_t)t.tv_sec * 1000 + (uint64_t)t.tv_usec / 1000);
}
