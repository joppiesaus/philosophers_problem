/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/11 13:56:52 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/27 15:31:11 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* I wrote all of this, then found out I just could've used printf...
 * these functions just write strings/numbers/chars to a string, without
 * null terminating them. It updates the index as well. It does NO
 * BOUNDS CHECKING.
 */
#include "util.h"

void	writer_wr_char(char *dst, size_t *i, const char c)
{
	dst[*i] = c;
	(*i)++;
}

/* if the compiler is smart it should inline wr_char */
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

	end = str + len - 1;
	while (str < end)
	{
		tmp = *str;
		*str = *end;
		*end = tmp;
		str++;
		end--;
	}
}

/* I wish I could use a do-while loop... */
void	writer_wr_uint(char *dst, size_t *i, uint64_t nbr)
{
	size_t	len;

	len = 0;
	while (1)
	{
		dst[*i + len] = (nbr % 10) + '0';
		nbr /= 10;
		len++;
		if (nbr == 0)
		{
			break ;
		}
	}
	m_rev_arr(dst + *i, len);
	*i += len;
}
