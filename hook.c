/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/16 19:06:09 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ASSERT_FAIL ft_puterror("Error initializing libmlx!");exit(1)
#include "wrapper.h"

void		look_at(t_ctx *c, const t_vec3 direction)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	from;
	t_vec3	to;

	from = V3(c->view->m[3][0], c->view->m[3][1], c->view->m[3][2]);
	to = V3_PLUS_V3(from, direction);
	forward = vec3_normalize(V3_MINUS_V3(from, to));
	right = vec3_cross_product(V3(0, 1, 0), forward);
	up = vec3_cross_product(forward, right);
	c->view->m[0][0] = right.x;
	c->view->m[0][1] = right.y;
	c->view->m[0][2] = right.z;
	c->view->m[1][0] = up.x;
	c->view->m[1][1] = up.y;
	c->view->m[1][2] = up.z;
	c->view->m[2][0] = forward.x;
	c->view->m[2][1] = forward.y;
	c->view->m[2][2] = forward.z;
}

static void	del_buff(t_list *elem)
{
	buffer_del(elem->content);
}

int			hook_exit(int key, t_ctx *c)
{
	if (key == 53)
	{
		ft_lstiter(c->buffs, del_buff);
		ft_lstdel(&c->buffs, NULL);
		mlx_destroy_window(c->mlx, c->win);
		free(c->view);
		free(c->mlx);
		free(c);
		exit(0);
	}
	if (key == 13)
		c->view->m[3][2] += 0.05;
	if (key == 1)
		c->view->m[3][2] -= 0.05;
	if (key == 0)
		c->view->m[3][0] += 0.05;
	if (key == 2)
		c->view->m[3][0] -= 0.05;
	if (key == 49)
		c->view->m[3][1] += 0.05;
	if (key == 256)
		c->view->m[3][1] -= 0.05;
	look_at(c, V3(5, -2, 5));
	return (0);
}

t_ctx		*initalize(void)
{
	t_ctx	*c;

	ASSERT(c = malloc(sizeof(t_ctx)));
	ASSERT(c->mlx = mlx_init());
	ASSERT(c->win = mlx_new_window(c->mlx, WIN_X, WIN_Y, WINDOW_NAME));
	c->buffs = NULL;
	c->view = mat_new(4);
	mlx_hook(c->win, 2, 0, hook_exit, c);
	c->past_time = time(NULL);
	return (c);
}
