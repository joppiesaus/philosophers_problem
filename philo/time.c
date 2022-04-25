/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 14:20:11 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/22 18:06:25 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

#include <unistd.h> /* usleep */
#include <sys/time.h> /* gettimeofday */

/* returns the amount of ms since the program began. */
uint64_t	get_time_since_start(const t_vars *vars)
{
	return (get_time() - vars->start_timestamp);
}

/* returns the current unix time in _milli_seconds(NOT seconds) */
uint64_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((uint64_t)t.tv_sec * 1000 + (uint64_t)t.tv_usec / 1000);
}

/* sleeps for ms milliseconds.*/
int	msleep(uint64_t ms)
{
	return (usleep(ms * 1000));
}
