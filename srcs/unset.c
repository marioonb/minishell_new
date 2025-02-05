/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**delete_env_element(int j, char **env)
{
	char	**env_new;
	int		i;
	int		ligne;
	int		k;

	k = 0;
	ligne = 0;
	env_new = NULL;
	while (env[ligne] != NULL)
		ligne++;
	i = 0;
	env_new = malloc(sizeof(char*) * (ligne));
	if (!env_new)
		ft_error_malloc();
	while (i < ligne)
	{
		if (i != j)
		{
			env_new[k] = ft_strdup(env[i]);
			k++;
		}
		i++;
	}
	env_new[k] = NULL;
	return (env_new);
}

static void	change_env_supp(int i, t_env *env)
{
	char	**new_env;

	new_env = delete_env_element(i, env->env);
	free_tab_char(env->env);
	env->env = duplicate_tab_char(new_env);
	free_tab_char(new_env);
}

static void	change_export_supp(int i, t_env *env)
{
	char	**new_export;

	new_export = delete_env_element(i, env->export);
	free_tab_char(env->export);
	env->export = duplicate_tab_char(new_export);
	free_tab_char(new_export);
}

static void	change_var_tab(t_env *env, char *str)
{
	int		i;

	i = 0;
	while (env->env[i])
	{
		if (ft_strncmp(str, env->env[i], ft_strlen(str)) == 0)
		{
			change_env_supp(i, env);
			break ;
		}
		i++;
	}
	i = 0;
	while (env->export[i])
	{
		if (ft_strncmp(str, env->export[i], ft_strlen(str)) == 0)
		{
			change_export_supp(i, env);
			break ;
		}
		i++;
	}
}

void		builtin_unset(char **tab, t_env *env)
{
	int		j;

	j = 1;
	if (tab[1])
		check_name_var(tab[1]);
	while (tab[j])
	{
		change_var_tab(env, tab[j]);
		j++;
	}
}
