/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/10 18:32:38 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ASSERT_FAIL ft_puterror("Error allocating buffer!");exit(1)
#include "wrapper.h"

t_buff		*buffer_new(t_ctx *c, unsigned x, unsigned y)
{
	t_buff *b;

	ASSERT(b = malloc(sizeof(t_buff)));
	b->ctx = c;
	ASSERT(b->obj = mlx_new_image(c->mlx, x, y));
	b->data = mlx_get_data_addr(b->obj, &b->depth, &b->width, &b->endianess);
	b->x = x;
	b->y = y;
	return (b);
}

void		buffer_point(t_buff *b, unsigned x, unsigned y, unsigned color)
{
	char *data;

	data = b->data + b->width * y + 4 * x;
	ft_memcpy(data, &color, sizeof(color));
}

void		buffer_blit(t_buff *b, unsigned x, unsigned y)
{
	mlx_put_image_to_window(b->ctx->mlx, b->ctx->win, b->obj, x, y);
}

void		buffer_del(t_buff *b)
{
	mlx_destroy_image(b->ctx->mlx, b->obj);
	free(b);
}
