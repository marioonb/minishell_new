#include "../include/minishell.h"

void check_error_quote(char *tab)
{
	int quote;

	quote = 1;
	int i;
	i = 1;
	while (tab[i])
	{
		if (tab[i] == '"' && tab[i-1] != '\'')
		{
			quote *= -1;
			i++;
			while (tab[i++] && quote < 0)
			{
				if (tab[i] == '"' && tab[i-1] != '\\')
					quote *= -1;
				i++;
			}
		}
		else if (tab[i] == '\'' && tab[i-1] != '\\')
		{
			quote *= -1;
			i++;
			while (tab[i++] && quote < 0)
			{
				if (tab[i] == '\'' && tab[i-1] != '\\')
					quote *= -1;
				i++;
			}
		}
		else
			i++;
	}
	if (quote < 0)
	{
		printf("erreur");
		exit (EXIT_FAILURE);
	}
}
