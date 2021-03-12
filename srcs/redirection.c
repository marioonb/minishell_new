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

static int	open_files(char *s, t_ms *ms, char type)
{
	char	*files;
	int		fd;

	files = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (files == NULL)
		ft_error_malloc();
	ft_strncpy(files, s, ft_strlen(s));
	if (ms->red > 2 && type == '>')
		g_exit = ft_error(7, 2);
	if (ms->red > 1 && type == '<')
		g_exit = ft_error(6, 2);
	if (ms->red == 1 && type == '>')
		fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666);
	if (ms->red == 2 && type == '>')
		fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0666);
	if (type == '<')
		fd = open(files, O_RDONLY, 0666);
	free(files);
	return (fd);
}

static int	search_fd(char *str, t_ms *ms, char c)
{
	int		fd;

	fd = 1;
	ms->red = 0;
	while (*str != c)
		str++;
	while (*str == c)
	{
		ms->red++;
		str++;
	}
	if (!(caractere_red(str)))
	{
		g_exit = ft_error_char(1, 2, *str);
		return (0);
	}
	if ((ms->red > 1 && c == '<') || (ms->red > 2 && c == '>'))
	{
		g_exit = ft_error_char(2, 2, c);
		return (-1);
	}
	fd = open_files(str, ms, c);
	return (fd);
}

/*
** cherche si dans la ligne de commande complete, il y a une redirection >
** si oui elle cherche le nom du fichier et creait ce fichier
** renvoi le type de fd a la fonction appelante
*/

static int	ft_redirection(char **tab, char type, t_ms *ms, int *i)
{
	int		fd;

	fd = 1;
	if (only_chevron(tab[*i], ms, type))
	{
		if ((ms->red > 1 && type == '<') || (ms->red > 2 && type == '>'))
		{
			g_exit = ft_error_char(2, 2, type);
			return (-1);
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

int			b(char *str, char c)
{
	int		i;
	char	d;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		if (str[i] == DBLE_Q || str[i] == SIMPLE_Q)
		{
			d = str[i];
			i++;
			while (str[i] != d)
				i++;
		}
		if (str[i])
			i++;
	}
	return (1);
}

int			find_fd(char **t, t_ms *ms)
{
	int		i;
	int		fd;

	fd = 1;
	i = 0;
	while (t[i])
	{
		if (t[i] && fstrchr(t[i], '<') && n(t[i], '<') && b(t[i], '<') == 0)
			fd = ft_redirection(t, '<', ms, &i);
		else if (t[i] && fstrchr(t[i], '>') && n(t[i], '>') &&
		b(t[i], '>') == 0)
		{
			fd = ft_redirection(t, '>', ms, &i);
			if (fd == -1)
				break ;
			if (t[i] && !fstrchr(t[i], '>'))
			{
				ms->redplus = duplicate_end(t, i);
				break ;
			}
		}
		if (t[i] && (!fstrchr(t[i], '>') || !n(t[1], '>') || b(t[i], '>' == 0)))
			i++;
	}
	return (fd);
}
