/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:56:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/25 15:12:06 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

/* I bet these philosophers are thinking about Shopenhauer and David Benatar's
Better Never to Have Been. Free them from their eternal tornment. */

# include <pthread.h>
# include <stdint.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_vars
{
	uint64_t	start_timestamp;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	uint32_t	max_meals;
	uint32_t	is_max_meals_enabled;
}	t_vars;

/* I use thinker as an shorthand for philosopher, as
 * philosopher is a really long type name IMO. */
typedef struct s_thinker
{
	t_fork			*left_fork;
	t_fork			*right_fork;
	uint64_t		last_meal_timestamp;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		thread;
	uint32_t		number;
	uint32_t		meals_eaten;
	pthread_mutex_t	meals_eaten_mutex;
	t_vars			*vars;
}	t_thinker;

typedef struct s_table
{
	t_thinker		*guests;
	t_fork			*forks;
	t_vars			*vars;
	uint32_t		population;
	uint32_t		should_stop;
	pthread_mutex_t	should_stop_mutex;
	pthread_t		watchdog_thread;
}	t_table;

int			parse_args(int argc, char **argv, t_table *table);

int			init_table(t_table *table);
t_thinker	*init_guests(t_table *table);
t_fork		*init_forks(uint32_t amount);
int			init_threads(t_table *table);

void		take_fork(t_fork *fork);
void		return_fork(t_fork *fork);

void		*thinker_start_routine(void *arg);
void		thinker_print_msg(t_thinker *thinker, const char *msg);

void		eat(t_thinker *phil);
void		think(t_thinker *phil);
void		thinker_sleep(t_thinker *phil);
void		starve(t_thinker *phil);

void		*watchdog_routine(void *arg);

#endif
