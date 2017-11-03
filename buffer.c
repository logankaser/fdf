/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/02 20:51:51 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

t_ctx		*initalize()
{
	t_ctx	*c;

	ASSERT(c = malloc(sizeof(t_ctx)));
	ASSERT(c->mlx = mlx_init());
	ASSERT(c->win = mlx_new_window(c->mlx, WIN_X, WIN_Y, WINDOW_NAME));
	c->buffers = NULL;
	return (c);
}

t_buffer	*buffer_create(t_ctx *ctx, unsigned x, unsigned y)
{
	t_buffer *b;

	ASSERT(b = malloc(sizeof(t_buffer)));
	ASSERT(b->obj = mlx_new_image(ctx->mlx, x, y));
	b->data = mlx_get_data_addr(b->obj, &b->depth, &b->width, &b->endianess);
	return (b);
}

void		buffer_set_pixel(t_buffer *b, unsigned x, unsigned y, unsigned color)
{
	char *data;

	data = b->data + b->width * y + 4 * x;
	ft_memcpy(data, &color, sizeof(color));
}

void		buffer_blit(t_ctx *ctx, t_buffer *b, unsigned x, unsigned y)
{
	mlx_put_image_to_window(ctx, ctx->win, b->obj, x, y);
}

void		buffer_destroy(t_buffer *b)
{
	free(b->obj);
	free(b);
}
