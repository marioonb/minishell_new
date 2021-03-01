/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecttion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// type 1 = >, type 2 = <

int	open_files(char *s, t_ms *ms, char type)
{
	char	*files;
	int		fd;

	files = malloc (sizeof(char) * ft_strlen(s) + 1);
	if (files == NULL)
		ft_error_malloc();
	ft_strncpy(files, s, ft_strlen(s));
	if (ms->red > 2 && type == '>')
		g_exit = ft_error(7, 2);
	if (ms->red > 1 && type == '<')
		g_exit = ft_error(6, 2);
	if (ms->red == 1 && type == '>')
		fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666 );
	if (ms->red == 2 && type == '>')
		fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0666 );
	if (type == '<')
		fd = open(files, O_RDONLY, 0666 );
	free(files); // AJOUT +++++++++++++++++++++++++++++++++++++++++++++
	return (fd);
}

int	caractere_red(char *c) // ajoute de | \ ;
{
	if (*c == '?' && !c[1])
		return (0);
	if (*c == '#' || *c == '&' || *c == '*' || *c == '.' || *c == '/')
		return (0);
	return (1);
}

int	search_fd(char *str, t_ms *ms, char c)
{
	int	i;
	int	fd;

	fd = 1;
	i = 0;
	ms->red = 0;
	while (*str != c)
		str++;
	while (*str == c)
	{
		ms->red ++;
		str++;
	}
	if (!(caractere_red(str))) // si rien apres le chevrons c'est qui y en a qu un retournre 1
	{
		g_exit = ft_error_char(1, 2, *str);
		return (0);
	}
	fd = open_files(str, ms, c); // redirection <
	return (fd);
}

/* cherche si dans la ligne de commande complete, il y a une redirection >
* si oui elle cherche le nom du fichier et creait ce fichier
* renvoi le type de fd a la fonction appelante
*/

/*int	only_chevron(char *str, t_ms *ms, char c)
{
	int	i;

	i = 0;
	ms->red = 0;
	while (*str != c && *str != BACK_S)//
		str++;//
	while (*str == c)
	{
		ms->red++;
		str++;
	}
	if (!*str)
		return (1);
	return (0);
}*/

int	only_chevron(char *str, t_ms *ms, char c)
{
	int	i;

	i = 0;
	//mini_printf_fd(2, "%s debut de fct\n", str);
	ms->red = 0;
	while (str[i] != c && str[i] != BACK_S)//
		i++;//
	//mini_printf_fd(2, "%s apres bcl 1\n", str);
	if (str[i] == '\\')
		i = red_back(str, i, '>');
	//mini_printf_fd(2, "%s apres bcl 2", str);
	while (str[i] == c)
	{
		ms->red++;
		i++;
	}
	//mini_printf_fd(2, "%s fin\n", str);
	if (!str[i])
		return (1);
	return (0);
}

char	**duplicate_end(char **tab, int i)
{
	int		j;
	int		cpt;
	char	**env;

	j = i;
	cpt = 0;
	while (tab[i])
	{
		cpt++;
		i++;
	}
	env = malloc(sizeof(char*) * (cpt + 1));
	if (!env)
		return (0);
	i = 0;
	while (i < cpt)
	{
		env[i] = ft_strdup(tab[j]);
		i++;
		j++;
	}
	env[i] = NULL;
	return (env);
}

int	ft_redirection(char **tab, char type, t_ms *ms, int *i)
{
	int	fd;

	fd = 1;
	if (only_chevron(tab[*i], ms, type))
	{
		if ((ms->red > 1 && type == '<') || (ms->red > 2 && type == '>'))
		{
			g_exit = ft_error_char(2, 2, type);
			return (0);
		}
		*i = *i + 1;
		if (tab[*i])
			fd = open_files(tab[*i], ms, type);
		else
		{
			g_exit = ft_error(5, 2);
			return (-1);
		}
	}
	else
		fd = search_fd(tab[*i], ms, type);
	if (tab[*i])
		*i = *i + 1;
	return (fd);
}



int	find_fd(char **tab, t_ms *ms)
{
	int	i;
	int	fd;

	fd = 1;
	i = 0;
	while (tab[i])
	{
		//if (tab[i] && ft_strchr(tab[i], '<'))
		if (tab[i] && ft_strchr(tab[i], '<') && no_back(tab[i]))
			fd = ft_redirection(tab, '<', ms, &i);
		//else if (tab[i] && ft_strchr(tab[i], '>')
		else if (tab[i] && ft_strchr(tab[i], '>') && no_back(tab[i]))
		{
			fd = ft_redirection(tab, '>', ms, &i);
			if (tab[i] && !ft_strchr(tab[i], '>'))
			{
				ms->redplus = duplicate_end(tab, i);
				break ;
			}
		}
		if (tab[i] && (!ft_strchr(tab[i], '>') ||  !no_back(tab[1])))
			i++;
	}
	return (fd);
}
