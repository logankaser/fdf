/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:21:16 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/27 18:53:26 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	ft_bzero(void *m, size_t n)
{
	uint8_t		*b8;
	uint64_t	*b64;

	b8 = m;
	while (n && n % 8)
		b8[--n] = 0;
	n /= 8;
	b64 = m;
	while (n)
		b64[--n] = 0;
}
