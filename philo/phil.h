/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:56:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/08 17:28:14 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

# include <pthread.h>
# include <stdint.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

/* I use thinker as an shorthand for philosopher, as
 * philosopher is a really long type name IMO. */
typedef struct s_thinker
{
	t_fork		*left_fork;
	t_fork		*right_fork;
	uint32_t	number;
}	t_thinker;

typedef struct s_table
{
	t_thinker	*guests;
	t_fork		*forks;
	uint32_t	population;
}	t_table;

int			init_table(t_table *table, uint32_t population);
t_thinker	*init_guests(t_table *table, uint32_t amount);
t_fork		*init_forks(uint32_t amount);

void		take_fork(t_fork *fork);
void		return_fork(t_fork *fork);

void		eat(t_thinker *phil);
void		think(t_thinker *phil);
void		sleep(t_thinker *phil);
void		starve(t_thinker *phil);

#endif