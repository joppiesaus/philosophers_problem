/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:56:52 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/11 14:51:10 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	writer_wr_char(char *dst, size_t *i, const char c)
{
	dst[*i] = c;
	(*i)++;
}

void	writer_wr_str(char *dst, size_t *i, const char *str)
{
	while (*str)
	{
		writer_wr_char(dst, i, *str);
		str++;
	}
}

static void	m_rev_arr(char *str, const size_t len)
{
	char	*end;
	char	tmp;

	end = str + len;
	while (str < end)
	{
		tmp = *str;
		*str = *end;
		*end = tmp;
		str++;
		end--;
	}
}

void	writer_wr_uint(char *dst, size_t *i, size_t nbr)
{
	size_t	len;

	if (nbr == 0)
	{
		writer_wr_char(dst, i, '0');
		return ;
	}
	len = 0;
	while (nbr > 0)
	{
		dst[*i + len] = (nbr % 10) + '0';
		nbr /= 10;
		len++;
	}
	m_rev_arr(dst + *i, len);
	*i += len;
}
