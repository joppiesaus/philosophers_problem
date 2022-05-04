/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 15:17:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:40:15 by jobvan-d      ########   odam.nl         */
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
	sem_wait(table->should_stop_sem);
	table->should_stop = 1;
	sem_post(table->should_stop_sem);
}

int	should_stop_simulation(t_table *table)
{
	int	should_stop;

	sem_wait(table->should_stop_sem);
	should_stop = table->should_stop;
	sem_post(table->should_stop_sem);
	return (should_stop);
}
