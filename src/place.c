/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 21:00:05 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/10 21:00:06 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	token_heat(t_env *env, int x, int y)
{
	int	i;
	int	j;
	int	tmp1;
	int tmp2;
	int	x_original;
	int	heat;

	i = 0;
	x_original = x;
	heat = 0;
	while (i < env->token.height)
	{
		j = 0;
		x = x_original;
		while (j < env->token.width)
		{
			tmp1 = x;
			tmp2 = y;
			if (x < 0)
				x = env->map.width + x;
			if (y < 0)
				y = env->map.height + y;
			if (env->token.str[i * env->token.width + j] == '*')
				heat += env->map.heat[y * env->map.width + x];
			x = tmp1;
			y = tmp2;
			x++;
			j++;
		}
		y++;
		i++;
	}
	return (heat);
}

void		place_token(t_env *env)
{
	int	x;
	int	y;
	int	min;

	y = 1 - env->token.height;
	env->token.x = 0;
	env->token.y = 0;
	env->token.min = 2147483647;
	while (y < env->map.height)
	{
		x = 1 - env->token.width;
		while (x < env->map.width)
		{
			if (is_valid_place(env, x, y))
			{
				if (env->token.min > (min = token_heat(env, x, y)))
				{
					env->token.x = x;
					env->token.y = y;
					env->token.min = min;
				}
			}
			x++;
		}
		y++;
	}
	ft_printf("%d %d\n", env->token.y, env->token.x);
}
