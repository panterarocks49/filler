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

static int	check_around(t_env *env, int i, int j, char c)
{
	int	y;
	int	x;
	int	tmp1;
	int tmp2;
	int	count;

	y = i - 2;
	count = 0;
	while (y <= i + 2)
	{
		x = j - 2;
		while (x <= j + 2)
		{
			tmp1 = x;
			tmp2 = y;
			if (x < 0)
				x = env->map.width + x;
			if (y < 0)
				y = env->map.height + y;
			if (x >= env->map.width)
				x = x - env->map.width;
			if (y >= env->map.height)
				y = y - env->map.height;
			if (env->map.str[y * env->map.width + x] == c)
				count++;
			x = tmp1;
			y = tmp2;
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
				env->map.heat[i * env->map.width + j] = check_around(env, i, j, env->opponent);
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
	int	tmp1;
	int tmp2;
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
			tmp1 = x;
			tmp2 = y;
			if (x < 0)
				x = env->map.width + x;
			if (y < 0)
				y = env->map.height + y;
			if (x >= env->map.width)
				x = x - env->map.width;
			if (y >= env->map.height)
				y = y - env->map.height;
			idx = y * env->map.width + x;
			if (y < env->map.height && x < env->map.width
				&& idx != i * env->map.width + j)
				min = abs_min(min, env->map.heat[idx]);
			x = tmp1;
			y = tmp2;
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

// static void	mark_last_piece(t_env *env)
// {
// 	int i;
// 	int j;
// 	int y;
// 	int x;
// 	int	tmp1;
// 	int tmp2;

// 	if (!*env->token.str)
// 		return ;
// 	i = 0;
// 	x = env->token.x;
// 	y = env->token.y;
// 	while (i < env->token.height)
// 	{
// 		j = 0;
// 		x = env->token.x;
// 		while (j < env->token.width)
// 		{
// 			if (env->token.str[i * env->token.width + j] == '*')
// 			{
// 				tmp1 = x;
// 				tmp2 = y;
// 				if (x < 0)
// 					x = env->map.width + x;
// 				if (y < 0)
// 					y = env->map.height + y;
// 				if (x >= env->map.width)
// 					x = x - env->map.width;
// 				if (y >= env->map.height)
// 					y = y - env->map.height;
				
// 				if (env->map.str[y * env->map.width + x] == env->player)
// 					env->map.str[y * env->map.width + x] = ft_tolower(env->player);

// 				x = tmp1;
// 				y = tmp2;
// 			}
// 			j++;
// 			x++;
// 		}
// 		i++;
// 		y++;
// 	}
// }

void		create_heatmap(t_env *env)
{
	int	i;
	int j;

	init_heatmap(env);
	fill_heatmap(env);
	// mark_last_piece(env);
	i = 0;
	while (i < env->map.height)
	{
		j = 0;
		while (j < env->map.width)
		{
			if (env->map.heat[i * env->map.width + j] == -1)
				env->map.heat[i * env->map.width + j] = FT_MAX(env->map.width, env->map.height);
			// else if (env->map.heat[i * env->map.width + j] != -2)
			// {
			// 	env->map.heat[i * env->map.width + j] += check_around(env, i, j, env->player);
			// 	env->map.heat[i * env->map.width + j] -= check_around(env, i, j, ft_tolower(env->player));
			// }
			j++;
		}
		i++;
	}
	// i = -1;
	// while (i++ < env->map.width * env->map.height)
	// 	env->map.str[i] = ft_toupper(env->map.str[i]);
	print_heatmap(env);
	fprintf(env->debug, "\n\n");
}
