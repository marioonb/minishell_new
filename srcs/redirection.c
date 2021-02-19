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

int	open_files(char *s, t_ms *ms)
{
	char	*files;
	int		fd;

	files = malloc (sizeof(char) * ft_strlen(s) + 1);
	if (files == NULL)
		ft_error_malloc();
	ft_strncpy(files, s, ft_strlen(s));
	if (ms->red == 1)
		fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666 );
	if (ms->red == 2)
		fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0666 );
	free(files); // AJOUT +++++++++++++++++++++++++++++++++++++++++++++
	return(fd);
}

int caractere_red(char *c) // ajoute de | \ ;
{
	if (*c == '?' && !c[1])
		return(0);
	if (*c == '#'|| *c == '&'|| *c == '*' || *c == '.'|| *c == '/')
		return (0);
	return (1);

}

int search_fd(char *str, t_ms *ms)
{
	int	i;
	int	fd;

	i = 0;
	ms->red = 0;
	while (*str == '>')
	{
		ms->red ++;
		str++;
	}
	if (!(caractere_red(str))) // si rien apres le chevrons c'est qui y en a qu un retournre 1
	{
		ft_error(1, *str);
		return(0);
	}
	else
		fd = open_files(str, ms);
	return(fd);
}

/* cherche si dans la ligne de commande complete, il y a une redirection >
* si oui elle cherche le nom du fichier et creait ce fichier
* renvoi le type de fd a la fonction appelante
*/


int only_chevron(char *str, t_ms *ms)
{
	int	i;

	i = 0;
	ms->red = 0;
	while (*str == '>')
	{
		ms->red++;
		str++;
	}
	if (!*str)
		return (1);
	return(0);
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

int	find_fd(char **tab, t_ms *ms)
{
	int		fd;
	int		i;
	char	*files;

	files = NULL;
	fd = 1;
	i = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], '>'))
		{
			if (only_chevron(tab[i], ms))
			{
				i++;
				if (tab[i])
					fd = open_files(tab[i], ms);
				else
				{
					ms->exit = ft_error(5, 2);
					return(-1);
				}
			}
			else
				fd = search_fd(tab[i], ms);
			if (tab[i])
				i++;
			if (tab[i] && !ft_strchr(tab[i], '>'))
			{
				ms->redplus = duplicate_end(tab, i);
				break;
			}
		}
		if (tab[i] && !ft_strchr(tab[i], '>'))
			i++;
	}
	return (fd);
}

/*
int	find_fd(char **tab)
{
	int		fd;
	int		i;
	char	*files;
	int		red;

	files = NULL;
	fd = 1;
	i = 0;
	while (tab[i])
	{
		if (tab[i + 1] && ft_strchr(tab[i], '>'))
		{
			red = compt_red(tab[i]);
			files = malloc (sizeof(char) * ft_strlen(tab[i + 1]) + 1);
			if (files == NULL)
				ft_error_malloc();
			ft_strncpy(files, tab[i + 1], ft_strlen(tab[i + 1]));
			if (red == 1)
				fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666 );
			if (red == 2)
				fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0666 );
			free(files); // AJOUT +++++++++++++++++++++++++++++++++++++++++++++
		}
		i++;
	}
	return (fd);
}
*/
