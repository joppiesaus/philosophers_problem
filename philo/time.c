/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/12 14:20:11 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/27 14:27:47 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

#include <unistd.h> /* usleep */
#include <sys/time.h> /* gettimeofday */

#define SLEEP_STEP_US (100) /* amount of ms to sleep each sleeping "step" */
#define DEATH_CHECK_RATE_MS (5) /* check deaths every x ms */

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

/* sleeps for ms milliseconds. Also, checks for deaths.
 * returns 0 on fail/death, 1 on success.
* I kind of wished to deduplicate this function but it's too cumbersome. */
int	msleep_deathcheck(t_table *table, uint64_t ms)
{
	uint64_t	start_time;
	int			i;

	i = 0;
	start_time = get_time();
	while (get_time() - start_time < ms)
	{
		if (usleep(SLEEP_STEP_US) == -1)
			return (0);
		i++;
		if (i == (DEATH_CHECK_RATE_MS * 1000) / SLEEP_STEP_US)
		{
			pthread_mutex_lock(&table->should_stop_mutex);
			if (table->should_stop)
			{
				pthread_mutex_unlock(&table->should_stop_mutex);
				return (0);
			}
			pthread_mutex_unlock(&table->should_stop_mutex);
			i = 0;
		}
	}
	return (1);
}

/* sleeps for ms milliseconds.
 * it sleeps in steps because apparently usleep is kind of weird and tends to
 * sleep longer than it's supposed to on my system. */
int	msleep(uint64_t ms)
{
	uint64_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < ms)
	{
		if (usleep(SLEEP_STEP_US) == -1)
			return (0);
	}
	return (1);
}
