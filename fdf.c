/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/04 17:25:16 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	main(void)
{
	t_ctx	*c;

	c = initalize();
	ft_lstpush(&c->buffs, buffer_create(c, WIN_X, WIN_Y), sizeof(t_buff));
	draw_line(c->buffs->content, V2(512.5, 512), V2(800, 600), 0xFFFFFF);
	draw_line(c->buffs->content, V2(600, 300), V2(300, 900), 0xFFFFFF);
	draw_line(c->buffs->content, V2(700, 300), V2(1200, 300), 0xFFFFFF);
	draw_line(c->buffs->content, V2(700.2, 302), V2(1200.2, 302), 0xFFFFFF);
	draw_line(c->buffs->content, V2(700, 500), V2(1200, 550), 0xFFFFFF);
	mlx_expose_hook(c->win, draw, c);
	mlx_loop(c->mlx);
}
