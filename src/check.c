/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:59:38 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/10 20:59:42 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filler.h>

static int	check_place(t_env *env, int x, int y)
{
	if (x < 0)
		x = env->map.width + x;
	if (y < 0)
		y = env->map.height + y;
	if (x >= env->map.width)
		x = x - env->map.width;
	if (y >= env->map.height)
		y = y - env->map.height;
	if (env->map.str[y * env->map.width + x] == env->opponent)
		return (-1);
	if (env->map.str[y * env->map.width + x] == env->player)
		return (1);
	return (0);
}

int			is_valid_place(t_env *env, int x, int y)
{
	int i;
	int j;
	int original_x;
	int	touching;
	int	place;

	i = -1;
	original_x = x;
	touching = 0;
	while (++i < env->token.height && (j = -1) == -1)
	{
		x = original_x;
		while (++j < env->token.width)
		{
			if (env->token.str[i * env->token.width + j] == '*')
			{
				if ((place = check_place(env, x, y)) == -1
					|| (touching += place) > 1)
					return (0);
			}
			x++;
		}
		y++;
	}
	return (touching);
}
