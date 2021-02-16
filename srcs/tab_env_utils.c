/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** la fonction est appelé pour changer le tableau env
** elle appelle une fonction pour creer un tableau avec la ligne supplementaire a ajouter
** elle appel une focntion pour le dupliquer et le mettre dans la structure
*/

void	change_env_add (char *tab, t_env *env)
{
	char	**new_env;

	new_env = replace_for_add(tab, env->env);
	free_double_tab(env->env);
	env->env = duplicate_tab_char(new_env);
	free_double_tab(new_env);
}

/*
** cette fonction cherche dans le tableau env
** si elle trouve le binaire envoyé
** elle remplace la ligne avec la nouvelle variable
*/

void	replace_var_env(char *bin, char *str, t_env *env)
{
	int	i;

	i = 0;
	while (env->env[i])
	{
		if (strncmp(bin, env->env[i], ft_strlen(bin)) == 0)
			env->env[i] = ft_strdup(str);
		i++;
	}
}

char	**replace_for_add(char *str, char **env)
{
	char	**env_new;
	int		ligne;
	int		i;

	env_new = NULL;
	ligne = 0;
	while (env[ligne] != NULL)
		ligne++;
	i = 0;
	env_new = (char**)malloc(sizeof(char*) * (ligne + 2));
	if (!env_new)
		ft_error_malloc();
	while (i < ligne)
	{
		env_new[i] = ft_strdup(env[i]);
		i++;
	}
	env_new[i] = ft_strdup(str);
	env_new[i + 1] = NULL;
	return (env_new);
}
