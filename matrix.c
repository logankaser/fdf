/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/07 20:17:01 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include <math.h>

t_mat3	*mat3_x_mat3(const t_mat3 a, const t_mat3 b)
{
	int			i;
	int			j;
	t_mat3		*product;

	product = malloc(sizeof(t_mat3));
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			*product[i][j] =
				a[i][0] * b[0][j] +
				a[i][1] * b[1][j] +
				a[i][2] * b[2][j];
	}
	return (product);
}

t_mat4	*mat4_x_mat4(const t_mat4 a, const t_mat4 b)
{
	int			i;
	int			j;
	t_mat4		*product;

	product = malloc(sizeof(t_mat4));
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			*product[i][j] =
				a[i][0] * b[0][j] +
				a[i][1] * b[1][j] +
				a[i][2] * b[2][j] +
				a[i][3] * b[3][j];
	}
	return (product);
}

static void	mat_reduce(float **m, int pivot, int order)
{
	int i;
	int j;
	float factor;
	
	factor = m[pivot][pivot];
 	for (i = 0; i < order * 2; i++) {
		m[pivot][i] /= factor;
	}
	for (i = 0; i < order; i++) {
		if (i != pivot) {
			factor = m[i][pivot];
			for (j = 0; j < order * 2; j++) {
				m[i][j] = m[i][j] - m[pivot][j] * factor;
			}
		}
	}
}

/*
** Only for square matrix.
*/

t_mat3	*mat3_inverse(const t_mat3 m)
{
	float	**tmp;
	t_mat3	*inv;
	int		i;
	int		j;

	ASSERT(tmp = malloc(sizeof(float *) * 3));
	i = -1;
	while (++i < 3)
	{
		ASSERT(tmp[i] = malloc(sizeof(float) * 6));
		j = -1;
		while (++j < 6)
		{
			if (j < 3)
				tmp[i][j] = m[i][j];
			else
				tmp[i][j] = j == i + 3;
			ft_putnbr(tmp[i][j]);
			ft_putchar(' ');
			if (j == 5)
				ft_putchar('\n');
		}
	}
	i = -1;
	while (++i < 3)
		mat_reduce(tmp, i, 3);
	ASSERT(inv = malloc(sizeof(t_mat3)));
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			*inv[i][j] = tmp[i][j + 3];
		free(tmp[i]);
	}
	free(tmp);
	return (inv);
}

int		main()
{
	t_mat3	M = M3( 1, 3, 1,
				    1, 1, 2,
				    2, 3, 4);
	t_mat3	N = M3( 2, 9,-5,
				    0,-2, 1,
				   -1,-3, 2);
	int		i = -1;
	int		j;
	t_mat3	*p;

	p = mat3_x_mat3(M, N);
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			if (*p[i][j] >= 0)
				ft_putchar(' ');
			ft_putnbr(*p[i][j]);
			if (j != 2)
				ft_putstr(", ");
			else
				ft_putstr(" \n");
		}
	}
	free(p);
	return (0);
}
