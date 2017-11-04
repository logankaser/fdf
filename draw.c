/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/03 19:49:30 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include <math.h>

int			draw(t_ctx *c)
{
	t_list *bfs;

	bfs = c->buffs;
	while (bfs)
	{
		buffer_blit(c, bfs->content, 0, 0);
		bfs = bfs->next;
	}
	return (0);
}

static void	swap(double *a, double *b)
{
	double temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

static double	fpart(double x)
{
	return (x - floor(x));
}

static double	rfpart(double x)
{
	return (1 - fpart(x));
}

static unsigned mag(double x)
{
	unsigned char m;

	m = 255 * x;
	return (RGB(m,m,m));
}

void		draw_line(t_buff *bf, t_vec2 a, t_vec2 b)
{
	char steep;

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
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	double gradient = dy / dx;
	if (dx == 0.0)
		gradient = 1;
	double xend = floor(a.x + 0.5);
	double yend = a.y + gradient * (xend - a.x);
	double xgap = fpart(a.x + 0.5);
	double xpx11 = xend;
	double ypx11 = floor(yend);
	if (steep)
	{
		buffer_point(bf, ypx11, xpx11, mag(rfpart(yend) * xgap));
		buffer_point(bf, ypx11 + 1, xpx11, mag(fpart(yend) * xgap));
	}
	else
	{
		buffer_point(bf, xpx11, ypx11, mag(rfpart(yend) * xgap));
		buffer_point(bf, xpx11, ypx11 + 1, mag(fpart(yend) * xgap));
	}
	xend = floor(b.x + 0.5);
	yend = b.y + gradient * (xend - b.x);
	xgap = fpart(b.x + 0.5);
	double xpx12 = xend;
	double ypx12 = floor(yend);
    if (steep)
    {
        buffer_point(bf, ypx12, xpx12, mag(rfpart(yend) * xgap));
        buffer_point(bf, ypx12 + 1, xpx12, mag(fpart(yend) * xgap));
    }
    else
    {
        buffer_point(bf, xpx12, ypx12, mag(rfpart(yend) * xgap));
        buffer_point(bf, xpx12, ypx12 + 1, mag(fpart(yend) * xgap));
    }
	double x = xpx11 + 1;
	double intery = a.y;
	if (steep)
	{
		while (x < xpx12)
		{
			buffer_point(bf, floor(intery), x, mag(rfpart(intery)));
			buffer_point(bf, floor(intery), x + 1, mag(fpart(intery)));
			intery += gradient;
			++x;
		}
	}
	else
	{
		while (x < xpx12)
		{
			buffer_point(bf, x, floor(intery), mag(rfpart(intery)));
			buffer_point(bf, x, floor(intery) + 1, mag(fpart(intery)));
			intery += gradient;
			++x;
		}
	}
}
