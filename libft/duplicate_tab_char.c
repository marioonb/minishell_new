/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_tab_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:26:08 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/16 12:27:41 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**duplicate_tab_char(char **envp)
{
	char	**env;
	int		ligne;
	int		i;

	env = NULL;
	ligne = 0;
	while (envp[ligne] != NULL)
		ligne++;
	i = 0;
	env = malloc(sizeof(char*) * (ligne + 1));
	if (!env)
		return (0);
	while (i < ligne)
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
