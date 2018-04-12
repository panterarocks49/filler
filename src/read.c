/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 18:38:07 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/10 18:38:10 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "filler.h"

void	skip_line(void)
{
	char	*line;

	line = NULL;
	get_next_line(0, &line);
	free(line);
}

void	read_player(t_env *env)
{
	char	*line;

	line = NULL;
	get_next_line(0, &line);
	env->player = (ft_atoi(line + 10) == 1 ? 'O' : 'X');
	env->opponent = (ft_atoi(line + 10) == 1 ? 'X' : 'O');
	free(line);
}

void	read_map_size(t_env *env)
{
	char	*line;
	char	*ptr;

	get_next_line(0, &line);
	ptr = line;
	while (*ptr && !(*ptr >= '0' && *ptr <= '9'))
		ptr++;
	env->map.height = ft_atoi(ptr);
	while (*ptr && *ptr >= '0' && *ptr <= '9')
		ptr++;
	env->map.width = ft_atoi(ptr);
	free(line);
}

void	read_map(t_env *env)
{
	char	*line;
	int		i;
	int		j;
	int		k;

	line = NULL;
	skip_line();
	i = 0;
	k = 0;
	while (i++ < env->map.height)
	{
		j = 4;
		get_next_line(0, &line);
		while (line[j] && line[j] != '\n')
			env->map.str[k++] = line[j++];
		free(line);
	}
}

void	read_token(t_env *env)
{
	char	*line;
	char	*ptr;
	int		i;
	int		j;
	int		k;

	line = NULL;
	get_next_line(0, &line);
	ptr = line;
	while (*ptr && !(*ptr >= '0' && *ptr <= '9'))
		ptr++;
	env->token.height = ft_atoi(ptr);
	while (*ptr && *ptr >= '0' && *ptr <= '9')
		ptr++;
	env->token.width = ft_atoi(ptr);
	free(line);
	i = 0;
	k = 0;
	while (i++ < env->token.height)
	{
		j = 0;
		get_next_line(0, &line);
		while (line[j] && line[j] != '\n')
			env->token.str[k++] = line[j++];
		free(line);
	}
}