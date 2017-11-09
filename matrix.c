/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/08 18:37:45 by lkaser           ###   ########.fr       */
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

static void	mat_reduce(float m[4][8], int pivot, int order)
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
** Only for square matrix of order 4 and lower.
*/

t_mat		*mat_inverse(const t_mat *m)
{
	float	tmp[4][8];
	t_mat	*inv;
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 6)
			if (j < 3)
				tmp[i][j] = m->m[i][j];
			else
				tmp[i][j] = j == i + 3;
	}
	i = -1;
	while (++i < 3)
		mat_reduce(tmp, i, 3);
	inv = mat_new(m->order);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			inv->m[i][j] = tmp[i][j + 3];
	}
	return (inv);
}

int		main()
{
	t_mat	*M = mat_new(3);
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
			ft_putnbr(p->m[i][j]);
			if (j != 2)
				ft_putstr(", ");
			else
				ft_putstr(" \n");
		}
	}
	mat_del(p);
	mat_del(M);
	return (0);
}
