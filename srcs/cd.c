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

static void	exec_chdir(t_env *env)
{
	char	*oldpwd;
	int		lenght;
	int		lenght2;
	char	*pwd;

	oldpwd = NULL;
	pwd = NULL;
	lenght2 = 0;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
		pwd = ft_strdup("/");
	lenght = 4 + ft_strlen(pwd) + 1;
	oldpwd = find_var("PWD", env->env);
	if (oldpwd == NULL)
		oldpwd = ft_strdup("/");
	lenght2 = 7 + ft_strlen(oldpwd) + 1;
	concat_for_change(pwd, "PWD=", lenght, env);
	concat_for_change(oldpwd, "OLDPWD=", lenght2, env);
	free(pwd);
	free(oldpwd);
}

/*
** recherche les path oldpwd et pwd et les modifie
*/

static char	*ft_home(char *tab, t_env *env)
{
	char	*path;
	char	*path2;

	tab++;
	path = find_var("HOME", env->env);
	if (*tab != '/')
		ft_strlcat(path, "/", ft_strlen(path + 1));
	if (*tab)
	{
		path2 = ft_strjoinfree(path, tab);
		return (path2);
	}
	return (path);
}

int			builtin_cd(char **tab, t_env *env)
{
	char	*pwd;

	pwd = NULL;
	g_exit = 0;
	if (tab[1] && tab[2])
	{
		g_exit = ft_error(4, 1);
		return (0);
	}
	if (!tab[1] || (tab[1] && tab[1][0] == '~'))
	{
		if (tab[1] && tab[1][0] == '~')
			pwd = ft_home(tab[1], env);
		else
			pwd = find_var("HOME", env->env);
		if (chdir(pwd) == 0)
			exec_chdir(env);
		free(pwd);
		return (0);
	}
	if (chdir(tab[1]) == 0)
		exec_chdir(env);
	else
		g_exit = ft_error_str(3, tab[1], 1);
	return (1);
}
