/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_environnement_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	var_lenght (char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

/* recherche dans une chaine si un element de env s'y trouve
* si oui elle renvoi la ligen complete de env - le nom de varibqle jusqu'a =
* sinon elle renvoi NULL
*/

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
	if (ft_isalnum(c) || c == '_' ) // AJOUTER # pour unset, voir pour export
		return (1);
	else
		return (0);
}

void	check_name_var(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		g_exit = ft_error_str(1, str, 1);
	else
	{
		while (str[i] && str[i] != '=')
		{
			if (check_caractere_name_var(str[i]) == 0)
				g_exit = ft_error_str(1, str, 1);
			i++;
		}
	}
}
