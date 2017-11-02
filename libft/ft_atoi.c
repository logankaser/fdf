/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 10:02:58 by lkaser            #+#    #+#             */
/*   Updated: 2017/09/20 10:46:53 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	char			is_negative;
	unsigned int	out;

	out = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		++str;
	is_negative = *str == '-';
	if (is_negative || *str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		out *= 10;
		out += ((int)*str - 48);
		++str;
	}
	return (is_negative ? -out : out);
}
