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

#include "filler.h"

void		print_heatmap(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	while (i < env->map.height)
	{
		j = 0;
		while (j < env->map.width)
		{
			fprintf(env->debug, "%3d", env->map.heat[i * env->map.width + j]);
			j++;
		}
		fprintf(env->debug, "\n");
		i++;
	}
	fprintf(env->debug, "\n");
}

int			abs_min(int a, int b)
{
	if (a < 0 || b < 0)
		return (FT_MAX(a, b));
	else
		return (FT_MIN(a, b));
}

int			main(void)
{
	t_env	env;
	char	*line;

	// remove debug
	env.debug = fopen("debug.log", "w");

	line = NULL;
	read_player(&env);
	read_map_size(&env);
	if (!(env.map.str = ft_strnew(env.map.height * env.map.width)) ||
		!(env.token.str = ft_strnew(env.map.height * env.map.width)) ||
		!(env.map.heat = (int *)malloc(sizeof(int) * env.map.height * env.map.width)))
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
	fclose(env.debug);
		
	}

	fclose(env.debug);

	return (0);
}