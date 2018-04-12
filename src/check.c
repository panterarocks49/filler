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

#include "filler.h"

int		is_valid_place(t_env *env, int x, int y)
{
	int i;
	int j;
	int	tmp1;
	int tmp2;
	int original_x;
	int	touching;

	i = 0;
	original_x = x;
	touching = 0;
	while (i < env->token.height)
	{
		j = 0;
		x = original_x;
		while (j < env->token.width)
		{
			if (env->token.str[i * env->token.width + j] == '*')
			{
				tmp1 = x;
				tmp2 = y;
				if (x < 0)
					x = env->map.width + x;
				if (y < 0)
					y = env->map.height + y;
				if (x >= env->map.width || y >= env->map.height
					|| env->map.str[y * env->map.width + x] == env->opponent)
					return (0);
				if (env->map.str[y * env->map.width + x] == env->player)
					touching++;
				x = tmp1;
				y = tmp2;
			}
			j++;
			x++;
		}
		i++;
		y++;
	}
	if (touching == 1)
		return (1);
	return (0);
}
