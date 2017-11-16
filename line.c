/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/15 12:47:18 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include <math.h>
#define FPART(x) (x - floor(x))
#define RFPART(x) (1 - FPART(x))

static void		swap(float *a, float *b)
{
	float temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

static unsigned	shade(unsigned c, const float x)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	r = (c & 0xFF) * x;
	g = (c >> 8 & 0xFF) * x;
	b = (c >> 16 & 0xFF) * x;
	return (RGB(r,g,b));
}

void			draw_line_shallow(t_buff *buf, t_vec2 a, t_vec2 b, unsigned c)
{
	float gradient;
	float xend;
	float yend;
	float xgap;
	float xstart;

	gradient = b.x - a.x == 0.0 ? 1 : (b.y - a.y) / (b.x - a.x);
	xend = floor(a.x + 0.5);
	yend = a.y + gradient * (xend - a.x);
	xgap = FPART(a.x + 0.5);
	xstart = xend;
	buffer_point(buf, xstart, floor(yend), shade(c, RFPART(yend) * xgap));
	buffer_point(buf, xstart, floor(yend) + 1, shade(c, FPART(yend) * xgap));
	xend = floor(b.x + 0.5);
	yend = b.y + gradient * (xend - b.x);
	xgap = FPART(b.x + 0.5);
	buffer_point(buf, xend, floor(yend), shade(c, RFPART(yend) * xgap));
	buffer_point(buf, xend, floor(yend) + 1, shade(c, FPART(yend) * xgap));
	a.y += gradient;
	while (++xstart < xend)
	{
		buffer_point(buf, xstart, floor(a.y), shade(c, RFPART(a.y)));
		buffer_point(buf, xstart, floor(a.y) + 1, shade(c, FPART(a.y)));
		a.y += gradient;
	}
}

void			draw_line_steep(t_buff *buf, t_vec2 a, t_vec2 b, unsigned c)
{
	float gradient;
	float xend;
	float yend;
	float xgap;
	float xstart;

	gradient = b.x - a.x == 0.0 ? 1 : (b.y - a.y) / (b.x - a.x);
	xend = floor(a.x + 0.5);
	yend = a.y + gradient * (xend - a.x);
	xgap = FPART(a.x + 0.5);
	xstart = xend;
	buffer_point(buf, floor(yend), xstart, shade(c, RFPART(yend) * xgap));
	buffer_point(buf, floor(yend) + 1, xstart, shade(c, FPART(yend) * xgap));
	xend = floor(b.x + 0.5);
	yend = b.y + gradient * (xend - b.x);
	xgap = FPART(b.x + 0.5);
	buffer_point(buf, floor(yend), xend, shade(c, RFPART(yend) * xgap));
	buffer_point(buf, floor(yend) + 1, xend, shade(c, FPART(yend) * xgap));
	a.y += gradient;
	while (++xstart < xend)
	{
		buffer_point(buf, floor(a.y), xstart, shade(c, RFPART(a.y)));
		buffer_point(buf, floor(a.y) + 1, xstart, shade(c, FPART(a.y)));
		a.y += gradient;
	}
}

void			draw_line(t_buff *buf, t_vec2 a, t_vec2 b, unsigned color)
{
	char	steep;

	steep = fabs(b.y - a.y) > fabs(b.x - a.x);
	if (steep)
	{
		swap(&a.x, &a.y);
		swap(&b.x, &b.y);
	}
	if (a.x > b.x)
	{
		swap(&a.x, &b.x);
		swap(&a.y, &b.y);
	}
	if (steep)
		draw_line_steep(buf, a, b, color);
	else
		draw_line_shallow(buf, a, b, color);
}
