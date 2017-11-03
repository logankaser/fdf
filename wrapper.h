/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:03:56 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/02 20:46:46 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H
# define ASSERT_FAIL {ft_puterror("There was an error!");exit(1);}
# include "libft.h"
# include "mlx.h"

# define WIN_X 1920
# define WIN_Y 1080
# define WINDOW_NAME "FDF"

typedef struct		s_buffer
{
	int				depth;
	int				width;
	int				endianess;
	void			*obj;
	char			*data;
}					t_buffer;

typedef struct		s_ctx
{
	void			*mlx;
	void			*win;
	t_list			*buffers;
}					t_ctx;

t_ctx				*initalize();
t_buffer			*buffer_create(t_ctx *ctx, unsigned x, unsigned y);
void				buffer_set_pixel(t_buffer *b,
					unsigned x, unsigned y, unsigned color);
void				buffer_blit(t_ctx *ctx, t_buffer *b, unsigned x, unsigned y);
void				buffer_destroy(t_buffer *b);

#endif
