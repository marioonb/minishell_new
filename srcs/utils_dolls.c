/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dolls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_var_doll(char *tab, int fd, char **env)
{
	char	*str_var;
	int		i;
	char	*str;

	str = NULL;
	str_var = NULL;
	i = 0;
	str_var = malloc(sizeof(char) * ft_strlen(tab) + 1);
	if (str_var == NULL)
		ft_error_malloc();
	while (check_caractere_name_var(*tab) == 1)
		str_var[i++] = *tab++;
	str_var[i] = '\0';
	if ((str = find_var(str_var, env)) != NULL)
		ft_out(str, fd);
	free(str_var);
	free(str);
	printf("tab est a %s", tab);
	return (tab);
}

int	search_doll(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}


