#include "../include/minishell.h"

void	ft_error(int a, int nexit)
{
	if (a == 1)
		printf ("erreur de quotes");
	if (a == 2)
		mini_printf("exit\nminishell: exit: trop d'arguments");
	if (a == 3)
		mini_printf("error backslash");
	if (a == 4)
		mini_printf("minishell: cd: trop d'arguments");
	exit (nexit);
}

void	ft_error_char(int a, char c, int nexit)
{
	if (a == 1)
		mini_printf("le flag %c ne fonctionne pas", c);
	exit (nexit);
}

void	ft_error_str(int a, char *s, int nexit)
{
	if (a == 1)
		mini_printf("export: « %s » : identifiant non valable ", s);
	if (a == 2)
		mini_printf("env: «%s»: Aucun fichier ou dossier de ce type", s);
	if (a == 3)
		mini_printf("exit \nminishell: exit: %s : argument numérique nécessaire", s);
	if (a == 4)
		mini_printf("minishell: cd: %s: Aucun fichier ou dossier de ce type", s);
	exit (nexit);
}
