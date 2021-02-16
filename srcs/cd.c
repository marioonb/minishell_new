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

char	*check_path(char **tab, t_ms *ms)
{
	int	i;

	i = 0;
	if (tab[2])
	{
		ms->exit = ft_error(4, 1);
		return (NULL);
	}
	if (tab[1][i] == '.')
		while (tab[1][i] == '.')
			i++;
	if (!tab[1][i])
	{
		if (i == 2)
			return ("JE NE SAIS PAS");
	}
	return (tab[1]);
}

/* recherche dans une chaine si un element de env s'y trouve
* si oui elle renvoi la ligen complete de env - le nom de varibqle jusqu'a =
* sinon elle renvoi NULL
*/

int	var_lenght (char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

char	*find_var(char *str, char **env)
{
	int	i;
	int	lenght;

	i = 0;
	while (env[i])
	{
		lenght = var_lenght(env[i]);
		//printf ("env[i] = %s pos %d\n", env[i], i);
		//printf("lenght est a = %d\n", lenght);
		//printf("env[i] avant boucle = %s\n", env[i]);
		//		if (ft_strncmp(str, env[i], (int)ft_strlen(str)) == 0)
		if (ft_strncmp(str, env[i], lenght) == 0
			&& (int)ft_strlen(str) <= lenght)
			return (ft_substr(env[i] + 1, lenght, ft_strlen(env[i]) - lenght));
		i++;
	}
	return (NULL);
}

void	concat_for_change(char *s1, char *s2, int size, t_env *env)
{
	ft_strlcat(s2, s1, size);
	treat_var(s2, env);
	free(s2);
}
/* recherche les path oldpwd et pwd et les modifie
*/

void	exec_chdir(char **tab, char *pwd, t_env *env)
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
}

//void	builtin_cd(char **tab, t_env *env)

int	builtin_cd(char **tab, t_env *env, t_ms *ms)
{
	char	*pwd;

	pwd = NULL;
	ms->exit = 0;
	if (tab[1])
		pwd = check_path(tab, ms);
	if (tab[1] && pwd == NULL)
		return (0);
	if (chdir(tab[1]) == 0 || !tab[1])
		exec_chdir(tab, pwd, env);
	else
		ms->exit = ft_error_str(3, tab[1], 1);
	return (1); ////
}
