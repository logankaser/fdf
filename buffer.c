/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/03 18:33:38 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

t_buff		*buffer_create(t_ctx *ctx, unsigned x, unsigned y)
{
	t_buff *b;

	ASSERT(b = malloc(sizeof(t_buff)));
	ASSERT(b->obj = mlx_new_image(ctx->mlx, x, y));
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

void		buffer_blit(t_ctx *ctx, t_buff *b, unsigned x, unsigned y)
{
	mlx_put_image_to_window(ctx, ctx->win, b->obj, x, y);
}

void		buffer_destroy(t_buff *b)
{
	free(b->obj);
	free(b);
}
