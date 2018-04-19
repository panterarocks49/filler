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

#include <filler.h>

static int	add_heat_around(t_env *env, int i, int j)
{
	int	y;
	int	x;
	int	count;
	int a;

	y = i - 3;
	count = 0;
	while (y <= i + 3)
	{
		x = j - 3;
		while (x <= j + 3)
		{
			a = env->map.heat[safe_idx(env, x, y)];
			if (a < -1)
				a += FT_MAX(env->map.height, env->map.width);
			count += a;
			x++;
		}
		y++;
	}
	return (count);
}

static int	token_heat(t_env *env, int x, int y)
{
	int	i;
	int	j;
	int	x_original;
	int	heat;

	i = -1;
	x_original = x;
	heat = 0;
	while (++i < env->token.height)
	{
		j = -1;
		x = x_original;
		while (++j < env->token.width)
		{
			if (env->token.str[i * env->token.width + j] == '*')
				heat += add_heat_around(env, y, x);
			x++;
		}
		y++;
	}
	return (heat);
}

void		place_token(t_env *env)
{
	int	x;
	int	y;
	int	min;

	env->token.x = 0;
	env->token.y = 0;
	env->token.min = 2147483647;
	y = 0 - env->token.height;
	while (++y < env->map.height)
	{
		x = 0 - env->token.width;
		while (++x < env->map.width)
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
		}
	}
	ft_printf("%d %d\n", env->token.y, env->token.x);
}
