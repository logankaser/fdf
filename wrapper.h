/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:03:56 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/09 20:25:27 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H
# include "libft.h"
# include "mlx.h"

# define WIN_X 1920
# define WIN_Y 1080
# define CANVAS_X 2
# define CANVAS_Y 2
# define WINDOW_NAME "FDF"
# define RGB(r,g,b) ((r) + ((g) << 8) + ((b) << 16))
# define V2(x,y) ((t_vec2){x,y})
# define V3(x,y,z) ((t_vec3){x,y,z})
# define T(f,s) ((t_tuple){f, s})

typedef struct		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct		s_mat
{
	int				order;
	float			**m;
}					t_mat;

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
	t_mat			*view;
	t_list			*buffs;
}					t_ctx;

typedef struct		s_tuple
{
	void			*fst;
	void			*snd;
}					t_tuple;

t_buff				*buffer_create(t_ctx *ctx, unsigned x, unsigned y);
void				buffer_point(t_buff *b,
						unsigned x, unsigned y, unsigned color);
void				buffer_blit(t_ctx *ctx, t_buff *b, unsigned x, unsigned y);
void				buffer_destroy(t_buff *b);

t_ctx				*initalize();
int					blit(t_ctx *c);
void				draw_line(t_buff *bf, t_vec2 a, t_vec2 b, unsigned color);

t_mat				*mat_new(int order);
void				mat_del(t_mat *m);
t_mat				*mat_x_mat(const t_mat *a, const t_mat *b);
t_mat				*mat_inverse(const t_mat *m);
void				vec3_x_mat(t_vec3 v, t_mat *m, t_vec3 *result);
#endif
