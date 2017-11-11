/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/10 19:53:48 by lkaser           ###   ########.fr       */
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
	map = malloc(sizeof(t_vec3*) * 3);
	map[0] = malloc(sizeof(t_vec3) * 2);
	map[1] = malloc(sizeof(t_vec3) * 2);
	map[0][0] = V3(0,0,1);
	map[0][1] = V3(1,0,1);
	map[1][0] = V3(0,1,1);
	map[1][1] = V3(1,1,1);
	map[2] = NULL;
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

/*
** Perspective projection.
** Matrix math is done on the stack for speed.
*/

int		draw(t_tuple *state)
{
	t_vec3	**map = state->snd;
	t_ctx	*c = state->fst;
	t_mat	to_view;
	t_vec3	pos;

	mat_inverse(c->view, &to_view);
	vec3_x_mat(map[0][0], &to_view, &pos);
	pos.x = pos.x / -pos.z;
	pos.y = pos.y / -pos.z;
	if (fabsf(pos.x) > CANVAS_X / 2 || fabsf(pos.y) > CANVAS_Y / 2)
		return (0);
	pos.x = ((pos.x + CANVAS_X * 0.5) / CANVAS_X) * WIN_X;
	pos.y = (1 - ((pos.y + CANVAS_Y * 0.5) / CANVAS_Y)) * WIN_Y;
	buffer_point(c->buffs->content, (int)pos.x, (int)pos.y, 0xFFFFFF);
	blit_all(c);
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
	t_vec3	**map;
	t_tuple	*state;

	(void)argc;
	map = read_map(argv[1]);
	c = initalize();
	ft_lstpush(&c->buffs, buffer_new(c, WIN_X, WIN_Y), sizeof(t_buff));
	state = malloc(sizeof(t_tuple));
	*state = T(c,map);
	mlx_loop_hook(c->mlx, draw, state);
	//mlx_hook(c->win, 6, 0, mouse_hook, NULL);
	mlx_loop(c->mlx);
}
