/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/16 19:00:17 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ASSERT_FAIL ft_puterror("Error reading map.\n");exit(1)
#include "wrapper.h"
#include "fdf.h"
#include <fcntl.h>
#include <math.h>

static t_vec3	*parse_line(t_map *map, char *l, int y)
{
	int		i;
	int		x;
	int		len;
	t_vec3	*row;

	i = -1;
	len = 0;
	while (l[++i])
		if (l[i] == ' ' &&
			(ft_in_range(l[i + 1], '0', '9') || !l[i + 1] || l[i + 1] == '-'))
			++len;
	row = malloc(sizeof(t_vec3) * len);
	i = 0;
	x = -1;
	while (l[i] && ++x < len)
	{
		row[x] = V3(x, ft_atoi(l + i) * 0.2, y);
		while (l[i] && l[i] == ' ')
			++i;
		while (l[i] && (ft_in_range(l[i + 1], '0', '9') || l[i + 1] == '-'))
			++i;
		i = l[i] ? i + 1 : 0;
	}
	ASSERT((map->width ? map->width == x : 1) && (map->width = x) > 1);
	return (row);
}

static t_map	*read_map(char *mapfile)
{
	t_map		*map;
	int			fd;
	char		*line;
	int			y;
	int			ret;

	map = malloc(sizeof(t_map));
	map->width = 0;
	map->data = NULL;
	line = NULL;
	fd = open(mapfile, O_RDONLY);
	y = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ASSERT(ft_str_has_only(line, " \n-0123456789"));
		ft_lstpush(&map->data, parse_line(map, line, y), sizeof(t_vec3*));
		free(line);
		line = NULL;
		++y;
	}
	ASSERT(ret >= 0 && map->width > 1);
	return (map);
}

static t_bool	project(t_mat *to_view, t_vec3 pos, t_vec2 *raster)
{
	pos = vec3_x_mat(pos, to_view);
	pos.x /= -pos.z;
	pos.y /= -pos.z;
	if (fabsf(pos.x) >= CANVAS_X / 2.01 || fabsf(pos.y) >= CANVAS_Y / 2.01)
		return (0);
	raster->x = ((pos.x + CANVAS_X * 0.5) / CANVAS_X) * WIN_X;
	raster->y = (1 - ((pos.y + CANVAS_Y * 0.5) / CANVAS_Y)) * WIN_Y;
	return (1);
}

int				draw(t_map *map)
{
	t_mat	world;
	t_vec2	a;
	t_vec2	b;
	t_list	*r;
	int		i;

	r = map->data;
	mat_inverse(map->c->view, &world);
	while (r)
	{
		i = -1;
		while (++i < map->width)
		{
			if (!project(&world, ((t_vec3*)r->content)[i], &a))
				continue;
			if (i + 1 < map->width
				&& project(&world, ((t_vec3*)r->content)[i + 1], &b))
				draw_line(map->c->buffs->content, a, b, 0x0000FF);
			if (r->next && project(&world, ((t_vec3*)r->next->content)[i], &b))
				draw_line(map->c->buffs->content, a, b, 0xFF0000);
		}
		r = r->next;
	}
	blit_all(map->c);
	return (0);
}

int				main(int argc, char **argv)
{
	t_ctx	*c;
	t_map	*map;

	if (argc == 2)
	{
		map = read_map(argv[1]);
		c = initalize();
		map->c = c;
		ft_lstpush(&c->buffs, buffer_new(c, WIN_X, WIN_Y), sizeof(t_buff));
		mlx_loop_hook(c->mlx, draw, map);
		mlx_loop(c->mlx);
	}
}
