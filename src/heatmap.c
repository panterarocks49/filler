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

#include "filler.h"

static int	check_around(t_env *env, int i, int j)
{
	int	y;
	int	x;
	int	idx;
	int	count;

	y = i - 1;
	count = 0;
	while (y <= i + 1)
	{
		x = j - 1;
		while (x <= j + 1)
		{
			idx = y * env->map.width + x;
			if (y > -1 && x > -1 && idx < env->map.width * env->map.height
				&& env->map.str[idx] == env->opponent)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

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
				env->map.heat[i * env->map.width + j] = check_around(env, i, j);
			else
				env->map.heat[i * env->map.width + j] = -1;
			j++;
		}
		i++;
	}
}

static int	zero_min(int a, int b)
{
	if (a < 0 || b < 0)
		return (FT_MAX(a, b));
	else
		return (FT_MIN(a, b));
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
			idx = y * env->map.width + x;
			if (y > -1 && x > -1 && idx < env->map.width * env->map.height
				&& idx != i * env->map.width + j)
				min = zero_min(min, env->map.heat[idx]);
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

	i = 0;
	while (i < env->map.height)
	{
		j = 0;
		while (j < env->map.width)
		{
			min = min_around(env, i, j);
			if (min > -1)
				env->map.heat[i * env->map.width + j] = min + 1;
			j++;
		}
		i++;
	}
}

static int	is_not_filled(t_env *env)
{
	int	i;
	int j;

	i = 0;
	while (i < env->map.height)
	{
		j = 0; 
		while (j < env->map.width)
		{
			if (min_around(env, i, j) > -1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void		create_heatmap(t_env *env)
{
	int	i;
	int j;

	init_heatmap(env);
	while (is_not_filled(env))
		fill_heatmap(env);
	i = 0;
	while (i < env->map.height)
	{
		j = 0; 
		while (j < env->map.width)
		{
			if (env->map.heat[i * env->map.width + j] == -1)
				env->map.heat[i * env->map.width + j] = 99;
			j++;
		}
		i++;
	}
}