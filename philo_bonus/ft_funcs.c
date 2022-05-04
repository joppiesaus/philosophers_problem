/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_funcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/04 17:39:48 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/05/04 17:40:17 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> /* write */
#include <stdlib.h> /* exit */

static size_t	ft_strlen(const char *str)
{
	const char	*old_str = str;

	while (*str)
	{
		str++;
	}
	return (str - old_str);
}

void	ft_putstr_fd(const int fd, const char *msg)
{
	write(fd, msg, ft_strlen(msg));
}

void	pexit(const char *msg)
{
	ft_putstr_fd(2, msg);
	exit(1);
}
