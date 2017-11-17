/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/17 14:44:21 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ASSERT_FAIL ft_puterror("Error initializing libmlx!");exit(1)
#include "wrapper.h"
#include <math.h>

void		set_view(t_vec3 pos, float yaw, float pitch, t_mat *v)
{
	float	cos_pitch;
	float	cos_yaw;
	t_vec3	x_ax;
	t_vec3	y_ax;
	t_vec3	z_ax;

	cos_pitch = cos(pitch);
	cos_yaw = cos(yaw);
	pitch = sin(pitch);
	yaw = sin(yaw);
	x_ax = V3(cos_yaw, 0, -yaw);
	y_ax = V3(yaw * pitch, cos_pitch, cos_yaw * pitch);
	z_ax = V3(yaw * cos_pitch, -pitch, cos_pitch * cos_yaw);
	MAT_ROW(v->m[0], x_ax.x, y_ax.x, z_ax.x, 0);
	MAT_ROW(v->m[1], x_ax.y, y_ax.y, z_ax.y, 0);
	MAT_ROW(v->m[2], x_ax.z, y_ax.z, z_ax.z, 0);
	MAT_ROW(v->m[3],
	-V3_DOT(x_ax, pos), -V3_DOT(y_ax, pos), -V3_DOT(z_ax, pos), 1);
}

int			hook_mouse(int x, int y, t_ctx *c)
{
	c->yaw += x * MOUSE_SPEED;
	c->pitch += y * MOUSE_SPEED;
	set_view(c->pos, c->yaw, c->pitch, c->view);
	return (0);
}

static void	del_buff(t_list *elem)
{
	buffer_del(elem->content);
}

int			hook_keys(int key, t_ctx *c)
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
		c->pos.z -= 0.1;
	if (key == 1)
		c->pos.z += 0.1;
	if (key == 0)
		c->pos.x -= 0.1;
	if (key == 2)
		c->pos.x += 0.1;
	if (key == 49)
		c->pos.y += 0.1;
	if (key == 256)
		c->pos.y -= 0.1;
	set_view(c->pos, c->yaw, c->pitch, c->view);
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
	c->pos = V3(0, 0, 0);
	c->yaw = 0;
	c->pitch = 0;
	c->past_time = time(NULL);
	return (c);
}
