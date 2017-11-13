/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/12 17:28:47 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wrapper.h"
#include "fdf.h"
#include <fcntl.h>
#include <math.h>

t_map *read_map(char *mapfile, t_ctx *c)
{
	t_map	*map;
	t_vec3 *row;

	map = malloc(sizeof(t_map));
	map->c = c;
	map->width = 4;
	row = malloc(sizeof(t_vec3) * 4);
	row[0] = V3(0,0,0);
	row[1] = V3(0,0,0);
	row[2] = V3(0,0,0);
	row[3] = V3(0,0,0);
	ft_lstpush(&map->data, row, sizeof(t_vec3) * 4);
	(void)mapfile;
	return (map);
}

static t_bool	project(t_mat *to_view, t_vec3 pos, t_vec2 *raster)
{
	vec3_x_mat(pos, to_view, &pos);
	pos.x /= -pos.z;
	pos.y /= -pos.z;
	if (fabsf(pos.x) > CANVAS_X / 2 || fabsf(pos.y) > CANVAS_Y / 2)
		return (0);
	raster->x = ((pos.x + CANVAS_X * 0.5) / CANVAS_X) * WIN_X;
	raster->y = (1 - ((pos.y + CANVAS_Y * 0.5) / CANVAS_Y)) * WIN_Y;
	return (1);
}

int		draw(t_map *map)
{
	t_mat	to_view;
	t_vec2	raster;

	mat_inverse(map->c->view, &to_view);
	raster.x = 0;
	raster.y = 0;
	(void)project;
	buffer_point(map->c->buffs->content, (int)raster.x, (int)raster.y, 0xFFFFFF);
	blit_all(map->c);
	return (0);
}

/*
int		mouse_hook(int x,int y, void *param)
{
	(void)param;
	ft_putnbr(x);
	ft_putchar(' ');
	ft_putnbr(y);
	ft_putchar('\n');
	return (0);
}
*/

int		main(int argc, char **argv)
{
	t_ctx	*c;
	t_map	*map;

	if (argc == 2)
	{
		c = initalize();
		map = read_map(argv[1], c);
		ft_lstpush(&c->buffs, buffer_new(c, WIN_X, WIN_Y), sizeof(t_buff));
		mlx_loop_hook(c->mlx, draw, map);
		//mlx_hook(c->win, 6, 0, mouse_hook, NULL);
		mlx_loop(c->mlx);
	}
}
