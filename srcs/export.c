/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	treat_var2(t_env *env, int i, char *str)
{
	char *bin;
	char*cpy;

	bin = NULL;
	cpy = NULL;
	bin = find_bin(str, '=', i);
	cpy = find_var(bin, env->env);
	if (cpy != NULL)
		replace_var_env(bin, str, env);
	else
		change_env_add(str, env);
	free(cpy);
	cpy = NULL;
	cpy = find_var(bin, env->export);
	if (cpy != NULL)
		replace_var_export(bin, str, env);
	else
		change_export_add(str, env);
	free(bin);
	free(cpy);
}

void	treat_var(char *str, t_env *env)
{
	int		i;
	char	*bin;
	char	*cpy;

	cpy = NULL;
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (i < (int)ft_strlen(str))
		treat_var2(env, i, str);
	else
	{
		bin = find_bin(str, '\0', i);
		cpy = find_var(bin, env->export);
		if (cpy == NULL)
			change_export_add(str, env);
		free(bin);
		free(cpy);
	}
	//free(bin);
	//free(cpy);
}

void	builtin_export(char **tab, t_env *env, t_ms *ms)
{
	char	*str;
	int		i;
	int		fd;

	g_exit = 0;
	i = 1;
	str = NULL;
	fd = find_fd(tab, ms);
	if (!tab[i] || fd != 1)
		declare_x(env, fd);
	else
	{
		while (tab[i])
		{
			str = ft_strdup(tab[i]);
			check_name_var(str);
			treat_var(str, env);
			i++;
			free(str);
		}
	}
}
