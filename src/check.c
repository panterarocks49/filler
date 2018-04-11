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
			{// add other side
				if (x < 0 || y < 0 || (env->map.str[y * env->map.width + x] != '.'
					&& ft_toupper(env->map.str[y * env->map.width + x]) != env->player))
					return (0);
				if (ft_toupper(env->map.str[y * env->map.width + x]) == env->player)
					touching++;
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
