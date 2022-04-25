/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/25 15:17:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/25 15:26:14 by jobvan-d      ########   odam.nl         */
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
