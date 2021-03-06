/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:03:56 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/17 14:46:35 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H
# include "libft.h"
# include "mlx.h"
# include <time.h>

# define WIN_X 1024
# define WIN_Y 1024
# define CANVAS_X 2
# define CANVAS_Y 2
# define WINDOW_NAME "FDF"
# define MOUSE_SPEED 0.02
# define RGB(r,g,b) ((b) + ((g) << 8) + ((r) << 16))
# define V2(x,y) ((t_vec2){x,y})
# define V3(x,y,z) ((t_vec3){x,y,z})
# define V3_MINUS_V3(a,b) (V3(a.x - b.x, a.y - b.y, a.z - b.z))
# define V3_PLUS_V3(a,b) (V3(a.x + b.x, a.y + b.y, a.z + b.z))
# define V3_DOT(a,b) (a.x * b.x + a.y * b.y + a.z * b.z)
# define MAT_ROW(m,x,y,z,w) m[0] = x;m[1] = y;m[2] = z;m[3] = w

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
	float			m[4][4];
}					t_mat;

typedef struct		s_ctx
{
	void			*mlx;
	void			*win;
	t_mat			*view;
	t_vec3			pos;
	float			yaw;
	float			pitch;
	t_list			*buffs;
	time_t			past_time;
}					t_ctx;

typedef struct		s_buff
{
	t_ctx			*ctx;
	int				depth;
	int				width;
	int				endianess;
	int				x;
	int				y;
	void			*obj;
	char			*data;
}					t_buff;

t_buff				*buffer_new(t_ctx *c, unsigned x, unsigned y);
void				buffer_point(t_buff *b,
						unsigned x, unsigned y, unsigned color);
void				buffer_blit(t_buff *b, unsigned x, unsigned y);
void				buffer_del(t_buff *b);

t_ctx				*initalize();
int					hook_mouse(int x, int y, t_ctx *c);
int					hook_keys(int keycode, t_ctx *c);
int					blit_all(t_ctx *c);
void				draw_line(t_buff *bf, t_vec2 a, t_vec2 b, unsigned color);

t_mat				*mat_new(int order);
void				mat_del(t_mat *m);
t_mat				*mat_x_mat(const t_mat *a, const t_mat *b);
void				mat_inverse(const t_mat *m, t_mat *r);
t_vec3				vec3_x_mat(t_vec3 v, t_mat *m);
double				vec3_length(t_vec3 *v);
t_vec3				vec3_normalize(t_vec3 v);
t_vec3				vec3_cross_product(t_vec3 a, t_vec3 b);
t_vec3				vec3_minus_vec3(t_vec3 a, t_vec3 b);
#endif
