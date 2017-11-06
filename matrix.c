/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/05 18:19:12 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include <math.h>

t_mat3	*mat3_x_mat3(const t_mat3 a, const t_mat3 b)
{
	unsigned	i;
	unsigned	j;
	t_mat3		*product;

	product = malloc(sizeof(t_mat3));
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			*product[i][j] =
				a[i][0] * b[0][j] +
				a[i][1] * b[1][j] +
				a[i][2] * b[2][j];
			++j;
		}
		++i;
	}
	return (product);
}

t_mat4	*mat4_x_mat4(const t_mat4 a, const t_mat4 b)
{
	unsigned	i;
	unsigned	j;
	t_mat4		*product;

	product = malloc(sizeof(t_mat4));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			*product[i][j] =
				a[i][0] * b[0][j] +
				a[i][1] * b[1][j] +
				a[i][2] * b[2][j] +
				a[i][3] * b[3][j];
			++j;
		}
		++i;
	}
	return (product);
}

int	main()
{
	t_mat3	M = M3(1,0,0,
				   0,1,0,
				   0,0,1);
	t_mat3	N = M3(1,0,0,
				   0,1,0,
				   0,0,1);
	int		i = -1;
	int		j;
	t_mat3	*p;

	p = mat3_x_mat3(M, N);
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			ft_putnbr(*p[i][j]);
			if (j != 2)
				ft_putstr(", ");
			else
				ft_putstr(" \n");
		}
	}
	return (0);
}
