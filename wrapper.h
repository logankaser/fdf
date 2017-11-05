/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:03:56 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/04 17:57:21 by lkaser           ###   ########.fr       */
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
# define RGB(r,g,b) ((r) + ((g) << 8) + ((b) << 16))
# define V2(x,y) ((t_vec2){x,y})

typedef struct		s_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_buff
{
	int				depth;
	int				width;
	int				endianess;
	int				x;
	int				y;
	void			*obj;
	char			*data;
}					t_buff;

typedef struct		s_ctx
{
	void			*mlx;
	void			*win;
	t_list			*buffs;
}					t_ctx;

t_buff				*buffer_create(t_ctx *ctx, unsigned x, unsigned y);
void				buffer_point(t_buff *b,
						unsigned x, unsigned y, unsigned color);
void				buffer_blit(t_ctx *ctx, t_buff *b, unsigned x, unsigned y);
void				buffer_destroy(t_buff *b);

t_ctx				*initalize();
int					draw(t_ctx *c);
void				draw_line(t_buff *bf, t_vec2 a, t_vec2 b, unsigned color);

#endif
