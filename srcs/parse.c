/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Lit le buffer envoyé par l'utilisateur
** et separe chaque commande en double tableau de char
*/

void		ft_read_buffer(char *buffer, t_env *env, t_ms *ms)
{
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	if (empty(buffer))
	{
		tab = ft_split_space(buffer, ';');
		while (tab[i])
		{
			ft_parse(tab[i], env, ms);
			i++;
		}
		free_tab_char(tab);
	}
}

void		ft_parse(char *tab, t_env *env, t_ms *ms)
{
	ms->pipe = find_pipe(tab);
	if (ms->pipe > 0)
		ms->pipe++;
	if (ms->pipe > 0)
		execute_pipe(tab, env, ms);
	else if (ms->pipe == 0)
		execute_no_pipe(tab, env, ms);
}
