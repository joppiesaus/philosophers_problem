/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 16:57:39 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/12 15:40:18 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "phil.h"

void		writer_wr_char(char *dst, size_t *i, const char c);
void		writer_wr_str(char *dst, size_t *i, const char *str);
void		writer_wr_uint(char *dst, size_t *i, uint64_t nbr);

uint64_t	get_time(void);
uint64_t	get_time_since_start(t_vars *vars);

int			msleep(uint64_t ms);

#endif