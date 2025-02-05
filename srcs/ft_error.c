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
	ft_putstr_fd("erreur malloc", 2);
	exit(EXIT_FAILURE);
}

void	ft_error_exit(int a, char *s, int nexit)
{
	ft_putstr_fd("exit\n", 2);
	if (a == 1)
		mini_printf_fd(2,
		""RED"minishell: exit: %s : numeric argument required"SET"\n", s);
	if (a == 2)
		ft_putstr_fd(""RED"minishell: exit: too many arguments"SET"\n", 2);
	if (a == 3)
		mini_printf_fd(2, ""RED"minishell: %s, Is a directory\n"SET"", s);
	exit(nexit);
}

int		ft_error(int a, int nexit)
{
	if (a == 1)
		ft_putstr_fd(""RED"erreur de quotes"SET"\n", 2);
	if (a == 2)
		ft_putstr_fd(
		""RED"minishell: syntax error near unexpected token « ; »or « | »"SET
		"\n", 2);
	if (a == 3)
		ft_putstr_fd(""RED"error backslash"SET"\n", 2);
	if (a == 4)
		ft_putstr_fd(""RED"minishell: cd: trop d'arguments"SET"\n", 2);
	if (a == 5)
		ft_putstr_fd(""RED"aucun fichier de redirection spécifié"SET"\n", 2);
	if (a == 6)
		ft_putstr_fd(""PINK"plusieur < a ne pas gerer"SET"\n", 2);
	return (nexit);
}

int		ft_error_char(int a, int nexit, char c)
{
	if (a == 1)
		mini_printf_fd(2,
		""RED"minishell: erreur de redirection : '%c'"SET"\n", c);
	if (a == 2)
		mini_printf_fd(2, ""RED"parse error near '%c'"SET"\n", c);
	return (nexit);
}

int		ft_error_str(int a, char *s, int nexit)
{
	if (a == 1)
		mini_printf_fd(2,
		""RED"minishell: export: « %s » : not a valid identifier"SET"\n", s);
	if (a == 2)
		mini_printf_fd(2,
		""RED"minishell: env: «%s»: no such file or directory"SET"\n", s);
	if (a == 3)
		mini_printf_fd(2,
		""RED"minishell: cd: %s: no such file or directory"SET"\n", s);
	if (a == 4)
		mini_printf_fd(2, ""RED"%s : command not found"SET"\n", s);
	if (a == 5)
		mini_printf_fd(2,
		""RED"minishell: %s : is a directory"SET"\n", s);
	if (a == 6)
		mini_printf_fd(2,
		""RED"minishell: %s : Permission non accordée"SET"\n", s);
	if (a == 7)
		mini_printf_fd(2,
		""RED"minishell: %s : no such file or directory"SET"\n", s);
	return (nexit);
}
