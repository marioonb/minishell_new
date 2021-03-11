/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 07:45:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/03/11 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int			pipe_back(char *s, int i, char c)
{
	int		cpt;

	cpt = 0;
	while (s[i] == BACK_S)
	{
		i++;
		cpt++;
	}
	if (s[i] && s[i] == c && cpt % 2 != 0)
		i++;
	return (i);
}

int			find_pipe(char *tab)
{
	int		pipe;
	int		i;

	i = 0;
	pipe = 0;
	while (tab[i])
	{
		if (tab[i] == BACK_S)
			i = pipe_back(tab, i, PIPE);
		if (tab[i] && tab[i] == PIPE)
		{
			if (!tab[i + 1] || only_space(tab, i + 1))
			{
				g_exit = ft_error(3, 2);
				return (-1);
			}
			else
				pipe++;
		}
		if (tab[i])
			i++;
	}
	return (pipe);
}
