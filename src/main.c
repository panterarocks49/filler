/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 12:53:17 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/10 12:53:19 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filler.h>

int			main(void)
{
	t_env	env;

	read_player(&env);
	read_map_size(&env);
	if (!(env.map.str = ft_strnew(env.map.height * env.map.width)) ||
		!(env.token.str = ft_strnew(env.map.height * env.map.width)) ||
		!(env.map.heat =
			(int *)malloc(sizeof(int) * env.map.height * env.map.width)))
		return (-1);
	read_map(&env);
	create_heatmap(&env);
	read_token(&env);
	place_token(&env);
	while (1)
	{
		skip_line();
		read_map(&env);
		create_heatmap(&env);
		read_token(&env);
		place_token(&env);
	}
	return (0);
}
