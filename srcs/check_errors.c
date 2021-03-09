/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*check_quote_end(char *tab, char c, t_ms *ms)
{
	int	cpt;

	ms->quote *= -1;
	tab++;
	while (*tab && ms->quote < 0)
	{
		cpt = 0;
		if (*tab == BACK_S)
		{
			cpt++;
			tab++;
		}
		if (c == SIMPLE_Q)
		{
			if (*tab && *tab == SIMPLE_Q)
				ms->quote *= -1;
		}
		else if (c == DOUBLE_Q)
		{
			if (*tab && *tab == DOUBLE_Q && cpt % 2 == 0)
				ms->quote *= -1;
		}
		if (*tab)
			tab++;
	}
	return (tab);
}

static void	check_error_quote(char *tab, t_ms *ms)
{
	int	cpt;

	cpt = 0;
	while (*tab)
	{
		cpt = 0;
		while (*tab == BACK_S)
		{
			cpt++;
			tab++;
		}
		if (*tab == DOUBLE_Q && cpt % 2 == 0) // ICI
			tab = check_quote_end(tab, DOUBLE_Q, ms);
		else if (*tab == SIMPLE_Q && cpt % 2 == 0)
			tab = check_quote_end(tab, SIMPLE_Q, ms);
		else if (*tab)
			tab++;
	}
}

int	check_error_quotes1(char **tab, t_ms *ms)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		check_error_quote(tab[i], ms);
		if (ms->quote < 0)
		{
			g_exit = ft_error(1, 2);
			return (0);
		}
		i++;
	}
	ms->quote = 1;
	return (1);
}
