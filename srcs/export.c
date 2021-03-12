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

static void	treat_var2(t_env *env, int i, char *str)
{
	char	*bin;
	char	*cpy;

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

void		treat_var(char *str, t_env *env)
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
		bin = NULL;
		free(cpy);
		cpy = NULL;
	}
}

static char	*modif_var2(char *s2, char *res)
{
	char	d;
	char	*s3;

	d = *s2;
	s3 = ft_strtrim_char(s2, d);
	ft_strcat(res, s3);
	free(s3);
	s3 = NULL;
	return (res);
}

static char	*modif_var(char *tab)
{
	char	*bin;
	char	*s2;
	char	*res;
	int		i;

	i = 0;
	if (!strchr(tab, '='))
		return (NULL);
	while (tab[i] && tab[i] != '=')
		i++;
	res = ft_calloc(sizeof(char) * (strlen(tab) + 1), 1);
	bin = find_bin(tab, '=', i);
	ft_strcat(res, bin);
	ft_strcat(res, "=");
	s2 = ft_strrchr(tab, '=') + 1;
	if (*s2 == DBLE_Q || *s2 == SIMPLE_Q)
		res = modif_var2(s2, res);
	else
	{
		free(bin);
		free(res);
		return (NULL);
	}
	free(bin);
	return (res);
}

void		builtin_export(char **tab, t_env *env, t_ms *ms)
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
			if ((str = modif_var(tab[i])) == NULL)
				str = strdup(tab[i]);
			check_name_var(str);
			treat_var(str, env);
			i++;
			free(str);
		}
	}
}
