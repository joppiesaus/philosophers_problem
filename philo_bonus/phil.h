/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 17:56:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:44:19 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
idea: have a thread in main, waiting for amount of forks semaphores(i.e. two
 forks, two sem_waits), when everything done then sim should end.
 research if we just can kill the main thread.
*/

#ifndef PHIL_H
# define PHIL_H

# include <pthread.h> /* pthread */
# include <stdint.h> /* uint32_t */
# include <semaphore.h> /* semaphores */

# define MSEMFDPERM (0644)
# define MSEM_STDOUT_NAME "stdout_sem"
# define MSEM_FORK_NAME "forks_sem"
# define MSEM_SHOULD_STOP_NAME "shouldstop_sem"
# define MSEM_THINKER_FINISHED_NAME "thinkers_finished_sem"
# define MSEM_KILLER_NAME "killer_sem"
# define MSEM_PIDS_NAME "pids_sem"

# define MSEM_LAST_MEAL_NAME "lastmeal_sem"

typedef struct s_vars
{
	struct s_table	*table;
	uint64_t		start_timestamp;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		max_meals;
	uint32_t		is_max_meals_enabled;
}	t_vars;

/* I use thinker as an shorthand for philosopher, as
 * philosopher is a really long type name IMO. */
typedef struct s_thinker
{
	uint64_t		last_meal_timestamp;
	sem_t			*last_meal_sem;
	pthread_t		watchdog_thread;
	uint32_t		number;
	uint32_t		meals_eaten;
	t_vars			*vars;
}	t_thinker;

typedef struct s_table
{
	t_thinker		*thinker;
	t_vars			*vars;
	uint32_t		population;
	uint32_t		should_stop;
	sem_t			*fork_sem;
	sem_t			*should_stop_sem;
	sem_t			*stdout_sem;
	sem_t			*thinkers_finished_sem;
	sem_t			*killer_sem;
	sem_t			*pids_sem;
	pthread_t		killer_thread;
	pthread_t		thinkers_finished_thread;
	pid_t			*child_pids;
}	t_table;

int			parse_args(int argc, char **argv, t_table *table);

void		take_fork(t_thinker *thinker);
void		return_fork(t_thinker *thinker);

int			thinker_start_routine(t_table *table);
int			thinker_print_msg(t_thinker *thinker, const char *msg);
void		thinker_write_to_str(t_thinker *thinker, char *dst, size_t *i,
				const char *msg);

int			eat(t_thinker *phil);
int			think(t_thinker *phil);
int			thinker_sleep(t_thinker *hil);
void		starve(t_thinker *phil);

void		*watchdog_routine(void *arg);
void		*killer_routine(void *arg);
void		*thinkers_finished_routine(void *arg);

void		init_parent_sems(t_table *table);
int			init_child_sems(t_thinker *thinker);

#endif
