/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/04 17:55:08 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include <math.h>
#define FPART(x) (x - floor(x))
#define RFPART(x) (1 - FPART(x))

static void		swap(double *a, double *b)
{
	double temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

static unsigned	shade(unsigned c, double x)
{
	unsigned char m;

	(void)c;
	m = 255 * x;
	return (RGB(m, m, m));
}

void			draw_line_shallow(t_buff *buf, t_vec2 a, t_vec2 b, unsigned c)
{
	double gradient;
	double xend;
	double yend;
	double xgap;
	double xstart;

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
	while (++xstart < xend)
	{
		buffer_point(buf, xstart, floor(a.y), shade(c, RFPART(a.y)));
		buffer_point(buf, xstart, floor(a.y) + 1, shade(c, FPART(a.y)));
		a.y += gradient;
	}
}

void			draw_line_steep(t_buff *buf, t_vec2 a, t_vec2 b, unsigned c)
{
	double gradient;
	double xend;
	double yend;
	double xgap;
	double xstart;

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
	while (++xstart < xend)
	{
		buffer_point(buf, floor(a.y), xstart, shade(c, RFPART(a.y)));
		buffer_point(buf, floor(a.y), xstart + 1, shade(c, FPART(a.y)));
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
