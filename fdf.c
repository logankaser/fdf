/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/09 20:30:36 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wrapper.h"
#include <fcntl.h>
#include <math.h>

/*
** Array of pointers to arrays of structs.
*/

t_vec3 **read_map(char *mapfile)
{
	t_vec3 **map;

	(void)mapfile;
	map = malloc(sizeof(t_vec3*) * 2);
	map[0] = malloc(sizeof(t_vec3) * 2);
	map[1] = malloc(sizeof(t_vec3) * 2);
	map[0][0] = V3(0,0,1);
	map[0][1] = V3(1,0,1);
	map[1][0] = V3(0,1,1);
	map[1][1] = V3(1,1,1);
	return (map);
}

/*
void	read_map(char *mapfile)
{
	int fd;
	int ret;
	char map[10000];

	fd = open(mapfile, O_RDONLY);
	ret = read(fd, map, 10000);
	map[ret] = '\0';
	ft_putstr(map);
}
*/

int		draw(t_tuple *state)
{
	t_vec3	**map = state->snd;
	t_ctx	*c = state->fst;
	t_mat	*to_view;
	t_vec3	view;
	t_vec2	raster;

	to_view = mat_inverse(c->view);
	vec3_x_mat(map[0][0], to_view, &view);
	mat_del(to_view);
	raster.x = view.x / -view.z;
	raster.y = view.y / -view.z;
	raster.x = floor(((raster.x + CANVAS_X / 2) / CANVAS_X) * WIN_X);
	raster.y = floor((1 - ((raster.y + CANVAS_Y / 2) / CANVAS_Y)) * WIN_Y);
	ft_putnbr(raster.x);
	ft_putchar(' ');
	ft_putnbr(raster.y);
	ft_putchar('\n');
	return (0);
}

int		main(int argc, char **argv)
{
	t_ctx	*c;
	t_vec3	**map;
	t_tuple	*state;

	(void)argc;
	map = read_map(argv[1]);
	c = initalize();
	ft_lstpush(&c->buffs, buffer_create(c, WIN_X, WIN_Y), sizeof(t_buff));
	draw_line(c->buffs->content, V2(700, 500), V2(1200, 550), 0xFFFFFF);
	state = malloc(sizeof(t_tuple));
	*state = T(c,map);
	mlx_loop_hook(c->mlx, draw, state);
	mlx_expose_hook(c->win, blit, c);
	mlx_loop(c->mlx);
}
