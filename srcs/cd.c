/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// mettre exit a 0 ?

char	*check_path(char **tab, char **env)
{
	int	i;

	i = 0;
	if (tab[2])
	{
		g_exit = ft_error(4, 1);
		return (NULL);
	}
	if (tab[1][i] == '.')
		while (tab[1][i] == '.')
			i++;
	mini_printf_fd(2, "%d", i);
	if (!tab[1][i])
	{
		if (i == 2)
		{
			//ft_putstr_fd("deux point\n", 2);
			return (find_var("OLDPWD", env));
		}
		else if (i == 1)
		{
			//ft_putstr_fd("rien\n", 2);
			return(NULL);
		}
	}
	return (tab[1]);
}

static void	concat_for_change(char *s1, char *var, int size, t_env *env)
{
	char	*copy;

	copy = NULL;
	copy = malloc(sizeof(char) * (size));
	if (copy == NULL)
		ft_error_malloc();
	ft_strncpy(copy, var, ft_strlen(var) + 1);
	ft_strlcat(copy, s1, size);
	treat_var(copy, env);
	free(copy);
}

static void	exec_chdir(char *pwd, t_env *env)
{
	char	*oldpwd;
	int		lenght;

	oldpwd = NULL;
	lenght = 4 + ft_strlen(pwd) + 1;
	concat_for_change(pwd, "PWD=", lenght, env);
	oldpwd = find_var("PWD", env->env);
	lenght = 7 + ft_strlen(oldpwd) + 1;
	concat_for_change(oldpwd, "OLDPWD=", lenght, env);
	free(pwd);
	free(oldpwd);
}

/*
** recherche les path oldpwd et pwd et les modifie
*/

/*static void	exec_chdir(char **tab, char *pwd, t_env *env)
{
	char	*oldpwd;
	int		lenght;
	char	*pwd2;
	char	*oldpwd2;

	oldpwd2 = NULL;
	oldpwd = NULL;
	pwd2 = NULL;
	if (!tab[1])
		pwd = find_var("HOME", env->env);
	lenght = 4 + ft_strlen(pwd) + 1;
	pwd2 = malloc(sizeof(char) * (lenght));
	if (pwd2 == NULL)
		ft_error_malloc();
	ft_strncpy(pwd2, "PWD=", 5);
	concat_for_change(pwd, pwd2, lenght, env);
	oldpwd = find_var("PWD", env->env);
	lenght = 7 + ft_strlen(oldpwd) + 1;
	oldpwd2 = malloc(sizeof(char) * (lenght));
	if (oldpwd2 == NULL)
		ft_error_malloc();
	ft_strncpy(oldpwd2, "OLDPWD=", 8);
	concat_for_change(oldpwd, oldpwd2, lenght, env);
}*/

//void	builtin_cd(char **tab, t_env *env)

int	builtin_cd(char **tab, t_env *env)
{
	char	*pwd;

	pwd = NULL;
	g_exit = 0;
	if (!tab[1])
	{
		//ft_putstr_fd("retour au home\n", 2);
		pwd = find_var("HOME", env->env);
		if (chdir(pwd) == 0)
		exec_chdir(pwd, env);
		return(0);
	}
	if (tab[1])
		pwd = check_path(tab, env->env);
	if (tab[1] && pwd == NULL)
		return (0);
	if (chdir(tab[1]) == 0)
		exec_chdir(pwd, env);
	else
		g_exit = ft_error_str(3, tab[1], 1);
	return (1);
}
