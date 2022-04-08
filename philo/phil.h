/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:56:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/08 16:43:18 by jobvan-d      ########   odam.nl         */
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

typedef struct s_philosopher
{
	uint32_t	number;
}	t_philosopher;

typedef struct s_table
{
	t_philosopher	*guests;
	t_fork			*forks;
	uint32_t		population;
}	t_table;

int				init_table(t_table *table, uint32_t population);
t_philosopher	*init_guests(uint32_t amount);
t_fork			*init_forks(uint32_t amount);

t_fork			*get_left_fork(t_table *table, t_philosopher *phil);
t_fork			*get_right_fork(t_table *table, t_philosopher *phil);

void			take_fork(t_fork *fork);
void			return_fork(t_fork *fork);

void			eat(t_philosopher *phil);
void			think(t_philosopher *phil);
void			sleep(t_philosopher *phil);
void			starve(t_philosopher *phil);

#endif