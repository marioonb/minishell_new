#include "../include/minishell.h"

int	check_error_quote(char *tab, int quote)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == '"' && (i == 0 || tab[i - 1] != '\\'))
		{
			quote *= -1;
			while (tab[++i] && quote < 0)
				if (tab[i] == '"' && tab[i - 1] != '\\')
					quote *= -1;
		}
		else if (tab[i] == '\'' && (i == 0 || tab[i - 1] != '\\'))
		{
			quote *= -1;
			while (tab[++i] && quote < 0)
				if (tab[i] == '\'')
					quote *= -1;
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

