/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/12 19:06:51 by lkaser           ###   ########.fr       */
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
	map->data = NULL;
	row = malloc(sizeof(t_vec3) * 4);
	row[0] = V3(0.1,0,1);
	row[1] = V3(0.2,0,1);
	row[2] = V3(0.3,0,1);
	row[3] = V3(0.4,0,1);
	ft_lstpush(&map->data, row, sizeof(row));
	row = malloc(sizeof(t_vec3) * 4);
	row[0] = V3(0.1,0.1,1);
	row[1] = V3(0.2,0.1,1);
	row[2] = V3(0.3,0.1,1);
	row[3] = V3(0.4,0.1,1);
	ft_lstpush(&map->data, row, sizeof(row));
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
	raster->x = floor(((pos.x + CANVAS_X * 0.5) / CANVAS_X) * WIN_X);
	raster->y = floor((1 - ((pos.y + CANVAS_Y * 0.5) / CANVAS_Y)) * WIN_Y);
	return (1);
}

int		draw(t_map *map)
{
	t_mat	to_view;
	t_vec2	a;
	t_vec2	b;
	t_list	*row;
	int		i;

	row = map->data;
	mat_inverse(map->c->view, &to_view);
	while (row)
	{
		i = -1;
		while (++i < map->width - 1)
		{
			if (!project(&to_view, ((t_vec3*)row->content)[i], &a)
				|| !project(&to_view, ((t_vec3*)row->content)[i + 1], &b))
				continue;
			draw_line(map->c->buffs->content, a, b, 0xFFFFFF);
			if (row->next)
				if (project(&to_view, ((t_vec3*)row->next->content)[i], &b))
					draw_line(map->c->buffs->content, a, b, 0xFFFFFF);
		}
		row = row->next;
	}
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
