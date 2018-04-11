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

static void	fill_algo(t_env *env)
{
	int	x;
	int	y;

	fprintf(env->debug, "%s", env->token.str);
	y = 1 - env->token.height;
	while (y < env->map.height - env->token.height)
	{
		x = 1 - env->token.width;
		while (x < env->map.width - env->token.width)
		{
			if (is_valid_place(env, x, y))
			{
				ft_printf("%d %d\n", y, x);
				return ;
			}
			x++;
		}
		y++;
	}
	ft_printf("0 0\n");
}

//act like my piece is eating his
//find a direction from my piece to his
//find a left and right to search for a place
//	will be up, down, left, right
//exand left or right depending on where he last expanded. do opposite?
static void	spider_algo(t_env *env)
{

}

void		place_token(t_env *env)
{
	//fill_algo(env);
	siper_algo(env);
}
