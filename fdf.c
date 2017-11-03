/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/02 20:59:11 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	main()
{
	t_ctx		*c;
	t_buffer	*b;

	c = initalize();
	//ft_lstpush(&c->buffers, buffer_create(c, WIN_X, WIN_Y));
	b = buffer_create(c, WIN_X, WIN_Y);
	int x = -1;
	int y;
	while(++x < 1920)
	{
		y = 529;
		while (++y < 550)
			buffer_set_pixel(b, x, y, mlx_get_color_value(c->mlx, 0xFF0000));
	}
	buffer_blit(c, b, 0, 0);
	mlx_loop(c->mlx);
}
