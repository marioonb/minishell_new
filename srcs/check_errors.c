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

/*int	check_error_quote(char *tab, int quote)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (tab[i])
	{
		cpt = 0;
		while (tab[i] == BACK_S)
		{
			cpt++;
			i++;
		}
		if (tab[i] == DOUBLE_Q && cpt % 2 == 0) // ICI
		{
			quote *= -1;
			while (tab[++i] && quote < 0)
			{
				cpt = 0;
				if (tab[i] == BACK_S)
				{
					cpt ++;
					i++;
				}
				if (tab[i] == DOUBLE_Q && cpt % 2 == 0)
					quote *= -1;
			}
		}
		else if (tab[i] == SIMPLE_Q && cpt % 2 == 0)
		{
			quote *= -1;
			while (tab[++i] && quote < 0)
			{
				cpt = 0;
				if (tab[i] == BACK_S)
				{
					cpt ++;
					i++;
				}
				if (tab[i] == SIMPLE_Q)
					quote *= -1;
			}
		}
		else if (tab[i]) // sinon ne marche pas avec echo \ ou echo \\ etc...
			i++;
	}
	return (quote);
}

int	check_error_quotes1(char **tab, t_ms *ms)
{
	int	i;
	int	quotes;
	//printf("%d dans check\n", exit->exit);
	i = 0;
	while (tab[i])
	{
		quotes = check_error_quote(tab[i], 1);
		if (quotes < 0)
		{
			ms->exit = ft_error(1, 2);
			//printf("%dapres l erreur\n", exit->exit);
			return (0);
		}
		i++;
	}
	return (1);
}
*/

/*int	check_error_quote(char *tab, int quote)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (tab[i])
	{
		cpt = 0;
		while (tab[i] == BACK_S)
		{
			cpt++;
			i++;
		}
		if (tab[i] == DOUBLE_Q && cpt % 2 == 0) // ICI
		{
			quote *= -1;
			while (tab[++i] && quote < 0)
			{
				cpt = 0;
				if (tab[i] == BACK_S)
				{
					cpt ++;
					i++;
				}
				if (tab[i] == DOUBLE_Q && cpt % 2 == 0)
					quote *= -1;
			}
		}
		else if (tab[i] == SIMPLE_Q && cpt % 2 == 0)
		{
			quote *= -1;
			while (tab[++i] && quote < 0)
			{
				cpt = 0;
				if (tab[i] == BACK_S)
				{
					cpt ++;
					i++;
				}
				if (tab[i] == SIMPLE_Q)
					quote *= -1;
			}
		}
		else if (tab[i]) // sinon ne marche pas avec echo \ ou echo \\ etc...
			i++;
	}
	return (quote);
}

int	check_error_quotes1(char **tab, t_ms *ms)
{
	int	i;
	int	quotes;
	//printf("%d dans check\n", exit->exit);
	i = 0;
	while (tab[i])
	{
		quotes = check_error_quote(tab[i], 1);
		if (quotes < 0)
		{
			ms->exit = ft_error(1, 2);
			//printf("%dapres l erreur\n", exit->exit);
			return (0);
		}
		i++;
	}
	return (1);
}*/

char	*check_quote_end(char *tab, char c, t_ms *ms)
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
			if (*tab && *tab ==  SIMPLE_Q)
				ms->quote *= -1;
		}
		else if (c == DOUBLE_Q)
		{
			if (*tab && *tab == DOUBLE_Q && cpt % 2 == 0)
				ms->quote *= -1;
		}
		tab++;
	}
	return (tab);
}

void	check_error_quote(char *tab, t_ms *ms)
{
	int	i;
	int	cpt;

	i = 0;
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
		else if (*tab) // sinon ne marche pas avec echo \ ou echo \\ etc...
			tab++;
	}
}
int	check_error_quotes1(char **tab, t_ms *ms)
{
	int	i;

	ms->quote = 1; // a retirer si init
	i = 0;
	while (tab[i])
	{
		check_error_quote(tab[i], ms);
		if (ms->quote < 0)
		{
			ms->exit = ft_error(1, 2);
			return (0);
		}
		i++;
	}
	ms->quote = 1;
	return (1);
}
