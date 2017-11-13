/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/12 17:24:45 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include <math.h>

void	vec3_x_mat(t_vec3 v, t_mat *m, t_vec3 *r)
{
	float	w;

	r->x = v.x * m->m[0][0] + v.y * m->m[1][0] + v.z * m->m[2][0] + m->m[3][0];
	r->y = v.x * m->m[0][1] + v.y * m->m[1][1] + v.z * m->m[2][1] + m->m[3][1];
	r->z = v.x * m->m[0][2] + v.y * m->m[1][2] + v.z * m->m[2][2] + m->m[3][2];
	w = v.x * m->m[0][3] + v.y * m->m[1][3] + v.z * m->m[2][3] + m->m[3][3];
	if (w != 1 && w)
	{
		r->x /= w;
		r->y /= w;
		r->z /= w;
	}
}
