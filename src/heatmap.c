/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 21:48:33 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/11 21:48:37 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filler.h>

static void	init_heatmap(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (i < env->map.height)
	{
		j = 0;
		while (j < env->map.width)
		{
			if (env->map.str[i * env->map.width + j] == env->player)
				env->map.heat[i * env->map.width + j] = -2;
			else if (env->map.str[i * env->map.width + j] == env->opponent)
				env->map.heat[i * env->map.width + j] = 1;
			else
				env->map.heat[i * env->map.width + j] = -1;
			j++;
		}
		i++;
	}
}

static int	min_around(t_env *env, int i, int j)
{
	int	y;
	int	x;
	int	idx;
	int	min;

	y = i - 1;
	min = -1;
	if (env->map.heat[i * env->map.width + j] != -1)
		return (-1);
	while (y <= i + 1)
	{
		x = j - 1;
		while (x <= j + 1)
		{
			idx = safe_idx(env, x, y);
			if (y < env->map.height && x < env->map.width
				&& idx != i * env->map.width + j)
				min = abs_min(min, env->map.heat[idx]);
			x++;
		}
		y++;
	}
	return (min);
}

static void	fill_heatmap(t_env *env)
{
	int		i;
	int		j;
	int		min;
	int		n;

	n = 1;
	while (n < FT_MAX(env->map.width, env->map.height))
	{
		i = 0;
		while (i < env->map.height)
		{
			j = 0;
			while (j < env->map.width)
			{
				min = min_around(env, i, j);
				if (min > -1 && min + 1 == n)
					env->map.heat[i * env->map.width + j] = min + 1;
				j++;
			}
			i++;
		}
		n++;
	}
}

void		create_heatmap(t_env *env)
{
	int	i;
	int j;

	init_heatmap(env);
	fill_heatmap(env);
	i = 0;
	while (i < env->map.height)
	{
		j = 0;
		while (j < env->map.width)
		{
			if (env->map.heat[i * env->map.width + j] == -1)
				env->map.heat[i * env->map.width + j] =
			FT_MAX(env->map.width, env->map.height);
			j++;
		}
		i++;
	}
}
