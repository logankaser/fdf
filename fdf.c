/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/03 19:50:25 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

int	main(void)
{
	t_ctx	*c;

	c = initalize();
	ft_lstpush(&c->buffs, buffer_create(c, WIN_X, WIN_Y), sizeof(t_buff));
	draw_line(c->buffs->content, V2(512, 512), V2(800, 800));
	draw_line(c->buffs->content, V2(512, 513), V2(800, 801));
	draw_line(c->buffs->content, V2(512, 514), V2(800, 802));
	mlx_expose_hook(c->win, draw, c);
	mlx_loop(c->mlx);
}
