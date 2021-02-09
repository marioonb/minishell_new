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

char	*find_bin(char *str, char c, int a)
{
	int		i;
	char	*strr;

	strr = NULL;
	i = 0;
	strr = malloc(sizeof(char) * a + 1);
	if (strr == NULL)
		ft_error_malloc();
	while (str[i] && str[i] != c)
	{
		strr[i] = str[i];
		i++;
	}
	strr[i] = '\0';
	return (strr);
}

// voir pour la faire en une seule avec check_name_var

int	check_caractere_name_var(char c)
{
	int	i;

	i = 0;
	if (ft_isalnum(c) || c == '_' ) // AJOUTER # pour unset, voir pour export
		return (1);
	else
		return (0);
}

void	check_name_var(char *str, t_exit *exit)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		exit->exit = ft_error_str(1, str, 1);
	else
	{
		while (str[i] && str[i] != '=')
		{
			if (check_caractere_name_var(str[i]) == 0)
				exit->exit = ft_error_str(1, str, 1);
			i++;
		}
	}
}

void	treat_var(char *str, t_env *env)
{
	int		i;
	char	*bin;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (i < (int)ft_strlen(str)) //&& strchr(str; '='))
	{
		bin = find_bin(str, '=', i);
		if (find_var(bin, env->env) != NULL)
			replace_var_env(bin, str, env);
		else
			change_env_add(str, env);
		if (find_var(bin, env->export) != NULL)
			replace_var_export(bin, str, env);
		else
			change_export_add(str, env);
	}
	else
	{
		bin = find_bin(str, '\0', i);
		if (!(find_var(bin, env->export) != NULL))
			change_export_add(str, env);
	}
	free(bin);
}

void	builtin_export(char **tab, t_env *env, t_exit *exit)
{
	char	*str;
	int		i;

	i = 1;
	str = NULL;
	if (!tab[i])
		declare_x(tab, env);
	else
	{
		while (tab[i])
		{
			str = ft_strdup(tab[i]);
			check_name_var(str, exit);
			treat_var (str, env);
			i++;
		}
	}
	free(str);
}
