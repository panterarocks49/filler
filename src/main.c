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

static FILE	*start_debug(void)
{
	FILE *fp;

	if (!(fp = fopen("debug.log", "w")))
		return (NULL);
	return (fp);
}

static void	end_debug(FILE *fp)
{
	fclose(fp);
}

int			main(void)
{
	t_env	env;
	char	*line;

	// remove debug
	env.debug = start_debug();

	line = NULL;
	read_player(&env);
	read_map_size(&env);
	if (!(env.map.str = ft_strnew(env.map.height * env.map.width))
		|| !(env.token.str = ft_strnew(env.map.height * env.map.width)))
		return (-1);
	read_map(&env);
	read_token(&env);
	place_token(&env);
	while (1)
	{
		skip_line();
		read_map(&env);
		read_token(&env);
		place_token(&env);
	}

	end_debug(env.debug);

	return (0);
}