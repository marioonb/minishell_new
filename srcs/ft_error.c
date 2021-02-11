/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_malloc(void)
{
	printf ("erreur malloc");
	exit (EXIT_FAILURE);
}

void	ft_error_exit (int a, char *s, int nexit)
{
	if (a == 1)
		mini_printf_fd(2, "exit \nminishell: exit: %s : argument numérique nécessaire\n", s);
	if (a == 2)
		ft_putstr_fd("exit\nminishell: exit: trop d'arguments\n", 2);
	exit (nexit);
}

int	ft_error(int a, int nexit)
{
	if (a == 1)
		ft_putstr_fd("erreur de quotes\n", 2);
	if (a == 2)
		ft_putstr_fd("command not found\n", 2);
	if (a == 3)
		ft_putstr_fd("error backslash", 2);
	if (a == 4)
		ft_putstr_fd("minishell: cd: trop d'arguments\n", 2);
	return(nexit);
}

void	ft_error_flag(char c)
{
	if (c == 'E' || c == 'e')
		mini_printf_fd(2, "oups... le flag -%c n'est pas à gérer...", c); // ne l utilise pas pour le moment
}

int	ft_error_str(int a, char *s, int nexit)
{
	if (a == 1)
		mini_printf_fd(2, "export: « %s » : identifiant non valable\n", s);
	if (a == 2)
		mini_printf_fd(2, "env: «%s»: Aucun fichier ou dossier de ce type\n", s);
	if (a == 3)
		mini_printf_fd(2, "minishell: cd: %s: Aucun fichier ou dossier de ce type\n", s);
	return (nexit);
}
