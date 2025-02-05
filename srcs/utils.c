/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 07:45:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/03/11 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			only_space(char *tab, int i)
{
	while (tab[i])
	{
		if (tab[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int			empty(char *s)
{
	int		cpt;

	cpt = 0;
	while (*s)
	{
		if (*s != ' ' && *s != ';' && *s != '|')
			return (1);
		if (*s == ';' || *s == '|')
			cpt++;
		s++;
	}
	if (cpt > 0)
		g_exit = ft_error(2, 2);
	return (0);
}

char		*modif_commande_quote(char *cmd)
{
	char	*str;
	int		c;

	if (cmd && (cmd[0] == DBLE_Q || cmd[0] == SIMPLE_Q))
	{
		c = cmd[0];
		str = ft_strtrim_char(cmd, c);
		ft_strncpy(cmd, str, ft_strlen(str));
		free(str);
		str = NULL;
	}
	return (cmd);
}
