/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:43:26 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/18 15:43:28 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filler.h>

static int	safe_x(t_env *env, int x)
{
	if (x < 0)
		x = env->map.width + x;
	else if (x >= env->map.width)
		x = x - env->map.width;
	return (x);
}

static int	safe_y(t_env *env, int y)
{
	if (y < 0)
		y = env->map.height + y;
	else if (y >= env->map.height)
		y = y - env->map.height;
	return (y);
}

int			safe_idx(t_env *env, int x, int y)
{
	return (safe_y(env, y) * env->map.width + safe_x(env, x));
}

int			abs_min(int a, int b)
{
	if (a < 0 || b < 0)
		return (FT_MAX(a, b));
	else
		return (FT_MIN(a, b));
}
