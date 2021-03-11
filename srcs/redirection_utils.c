/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 07:45:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/03/11 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		**duplicate_end(char **tab, int i)
{
	int		j;
	int		cpt;
	char	**env;

	j = i;
	cpt = 0;
	while (tab[i])
	{
		cpt++;
		i++;
	}
	env = malloc(sizeof(char*) * (cpt + 1));
	if (!env)
		return (0);
	i = 0;
	while (i < cpt)
	{
		env[i] = ft_strdup(tab[j]);
		i++;
		j++;
	}
	env[i] = NULL;
	return (env);
}

int			only_chevron(char *str, t_ms *ms, char c)
{
	int		i;

	i = 0;
	ms->red = 0;
	while (str[i] != c && str[i] != BACK_S)
		i++;
	if (str[i] == '\\')
		i = red_back(str, i, c);
	while (str[i] == c)
	{
		ms->red++;
		i++;
	}
	if (!str[i])
		return (1);
	return (0);
}
