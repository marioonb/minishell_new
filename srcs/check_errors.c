#include "../include/minishell.h"

/*int	check_error_quote(char *tab, int quote)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (tab[i])
	{
		// AJOUT
		cpt = 0;
		while (tab[i] == BACK_S)
		{
			cpt++;
			i++;
		}
		//if (tab[i] == DOUBLE_Q && (i == 0 || tab[i - 1] != BACK_S))
		//{
		//	quote *= -1;
		//	while (tab[++i] && quote < 0)
		//		if (tab[i] == DOUBLE_Q && tab[i - 1] != BACK_S)
		//			quote *= -1;
		//}
		if (tab[i] == DOUBLE_Q && cpt % 2 == 0) // ICI
		{
			quote *= -1;
			cpt = 0; /// AJOUT
			while (tab[++i] && quote < 0)
			{
				if (tab[i] == BACK_S)
					cpt ++;
				else if (tab[i] == DOUBLE_Q && cpt % 2 == 0) // AJOUT ELSE IF
					quote *= -1;
			}
		}
		else if (tab[i] == SIMPLE_Q && cpt % 2 != 0) // change avec && (i == 0 || tab[i - 1] != BACK_S)
		{
			quote *= -1;
			while (tab[++i] && quote < 0)
				if (tab[i] == SIMPLE_Q)
					quote *= -1;
		}
		else
			i++;
	}
	return (quote);
}*/

int	check_error_quote(char *tab, int quote)
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
		else
			i++;
	}
	return (quote);
}

void	check_error_quotes1(char **tab)
{
	int	i;
	int	quotes;

	i = 0;
	while (tab[i])
	{
		quotes = check_error_quote(tab[i], 1);
		if (quotes < 0)
			ft_error(1, 130);
		i++;
	}
}
