/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/09 15:55:14 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include <math.h>

t_mat		*mat_new(int order)
{
	t_mat	*new;
	int		i;
	int		j;

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

void		mat_del(t_mat *m)
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
	int			k;
	int			order;
	t_mat		*product;

	if ((order = a->order) != b->order)
		return (NULL);
	product = mat_new(order);
	i = -1;
	while (++i < order)
	{
		j = -1;
		while (++j < order)
		{
			k = -1;
			while (++k < order)
				product->m[i][j] += a->m[i][k] * b->m[k][j];
		}
	}
	return (product);
}

static void	mat_reduce(float tmp[4][8], int pivot, int order)
{
	int		i;
	int		j;
	float	factor;

	factor = tmp[pivot][pivot];
	i = -1;
	while (++i < order * 2)
		tmp[pivot][i] /= factor;
	i = -1;
	while (++i < order)
		if (i != pivot)
		{
			factor = tmp[i][pivot];
			j = -1;
			while (++j < order * 2)
				tmp[i][j] = tmp[i][j] - tmp[pivot][j] * factor;
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
			tmp[i][j] = j < m->order ? m->m[i][j] : j == i + m->order;
	}
	i = -1;
	while (++i < m->order)
		mat_reduce(tmp, i, m->order);
	i = -1;
	inv = mat_new(m->order);
	while (++i < m->order)
	{
		j = -1;
		while (++j < m->order)
			inv->m[i][j] = tmp[i][j + m->order];
	}
	return (inv);
}
