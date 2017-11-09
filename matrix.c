/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/08 19:42:29 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include <math.h>

t_mat		*mat_new(int order)
{
	t_mat	*new;
	int		i;
	int 	j;

	new = malloc(sizeof(t_mat));
	new->order = order;
	new->m = malloc(sizeof(float *) * order);
	i = -1;
	while (++i < order)
	{
		new->m[i] = malloc(sizeof(float) * order);
		j = -1;
		while (++j < order)
			new->m[i][j] = i == j;
	}
	return (new);
}

void	mat_del(t_mat *m)
{
	int		i;

	i = -1;
	while (++i < m->order)
		free(m->m[i]);
	free(m->m);
	free(m);
}

t_mat		*mat_x_mat(const t_mat *a, const t_mat *b)
{
	int			i;
	int			j;
	int 		k;
	t_mat		*product;

	product = mat_new(a->order);
	i = -1;
	while (++i < a->order)
	{
		j = -1;
		while (++j < a->order)
		{
			k = -1;
			while (++k < a->order)
				product->m[i][j] += a->m[i][k] * b->m[k][j];
		}
	}
	return (product);
}

static void	mat_reduce(float tmp[4][8], int pivot, int order)
{
	int i;
	int j;
	float factor;
	
	factor = tmp[pivot][pivot];
 	for (i = 0; i < order * 2; i++) {
		tmp[pivot][i] /= factor;
	}
	for (i = 0; i < order; i++) {
		if (i != pivot) {
			factor = tmp[i][pivot];
			for (j = 0; j < order * 2; j++) {
				tmp[i][j] = tmp[i][j] - tmp[pivot][j] * factor;
			}
		}
	}
}

/*
** Only for square matrix of order 4 and lower.
*/

t_mat		*mat_inverse(const t_mat *m)
{
	float	tmp[4][8];
	t_mat	*inv;
	int		i;
	int		j;

	i = -1;
	while (++i < m->order)
	{
		j = -1;
		while (++j < m->order * 2)
			if (j < m->order)
				tmp[i][j] = m->m[i][j];
			else
				tmp[i][j] = j == i + m->order;
	}
	i = -1;
	while (++i < m->order)
		mat_reduce(tmp, i, m->order);
	inv = mat_new(m->order);
	i = -1;
	while (++i < m->order)
	{
		j = -1;
		while (++j < m->order)
			inv->m[i][j] = tmp[i][j + m->order];
	}
	return (inv);
}

int		main()
{
	t_mat	*M = mat_new(3);
	M->m[0][0] = 2;
	M->m[0][1] = 9;
	M->m[0][2] = -5;

	M->m[1][0] = 0;
	M->m[1][1] = -2;
	M->m[1][2] = 1;
	
	M->m[2][0] = -1;
	M->m[2][1] = -3;
	M->m[2][2] = 3;
	int		i = -1;
	int		j;
	t_mat	*p;

	p = mat_inverse(M);
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			if (p->m[i][j] >= 0)
				ft_putchar(' ');
			printf("%f", p->m[i][j]);
			if (j == 2)
				printf("\n");
			else
				printf(", ");
		}
	}
	mat_del(p);
	mat_del(M);
	return (0);
}
