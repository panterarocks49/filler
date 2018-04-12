/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 12:54:00 by jbrown            #+#    #+#             */
/*   Updated: 2018/04/10 12:54:05 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_token
{
	int		width;
	int		height;
	int		x;
	int		y;
	int		min;
	char	*str;
}				t_token;

typedef struct	s_map
{
	int		width;
	int		height;
	int		*heat;
	char	*str;
}				t_map;

typedef struct	s_env
{
	// debug !!! remove
	FILE	*debug;

	t_map	map;
	t_token	token;
	char	player;
	char	opponent;
}				t_env;

void			skip_line(void);
void			read_player(t_env *env);
void			read_map_size(t_env *env);
void			read_map(t_env *env);
void			read_token(t_env *env);

int				is_valid_place(t_env *env, int x, int y);

void			place_token(t_env *env);

void			create_heatmap(t_env *env);




void		print_heatmap(t_env *env);


#endif