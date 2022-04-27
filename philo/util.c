/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 15:17:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/26 18:13:22 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

/* returns the lesser value of a and b. */
uint32_t	min(uint32_t a, uint32_t b)
{
	if (a < b)
	{
		return (a);
	}
	return (b);
}

/* sets the should_stop flag to 1 */
void	set_stop_flag(t_table *table)
{
	pthread_mutex_lock(&table->should_stop_mutex);
	table->should_stop = 1;
	pthread_mutex_unlock(&table->should_stop_mutex);
}

int	should_stop_simulation(t_table *table)
{
	int	should_stop;

	pthread_mutex_lock(&table->should_stop_mutex);
	should_stop = table->should_stop;
	pthread_mutex_unlock(&table->should_stop_mutex);
	return (should_stop);
}
