/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2017/11/10 19:56:52 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ASSERT_FAIL ft_puterror("Error initializing libmlx!");exit(1)
#include "wrapper.h"

static void	del_buff(t_list *elem)
{
	buffer_del(elem->content);
}

int			hook_exit(int key, t_ctx *c)
{
	if (key == 53)
	{
		ft_lstiter(c->buffs, del_buff);
		ft_lstdel(&c->buffs, NULL);
		mlx_destroy_window(c->mlx, c->win);
		free(c->view);
		free(c->mlx);
		free(c);
		exit(0);
	}
	return (0);
}

t_ctx		*initalize(void)
{
	t_ctx	*c;

	ASSERT(c = malloc(sizeof(t_ctx)));
	ASSERT(c->mlx = mlx_init());
	ASSERT(c->win = mlx_new_window(c->mlx, WIN_X, WIN_Y, WINDOW_NAME));
	c->buffs = NULL;
	c->view = mat_new(4);
	mlx_key_hook(c->win, hook_exit, c);
	return (c);
}
