/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 16:57:39 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:44:32 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "phil.h"

# define WRITER_BUF_LEN (128)

void		writer_wr_char(char *dst, size_t *i, const char c);
void		writer_wr_str(char *dst, size_t *i, const char *str);
void		writer_wr_uint(char *dst, size_t *i, uint64_t nbr);

uint64_t	get_time(void);
uint64_t	get_time_since_start(const t_vars *vars);

int			msleep(uint64_t ms);
int			msleep_deathcheck(t_table *table, uint64_t ms);

uint32_t	min(uint32_t a, uint32_t b);

void		set_stop_flag(t_table *table);
int			should_stop_simulation(t_table *table);

#endif
