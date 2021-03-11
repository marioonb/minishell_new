/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	flag_n(char *tab)
{
	int		i;

	i = 0;
	if (tab == NULL)
		return (0);
	if (tab[i] == '-')
	{
		i++;
		while (tab[i] && tab[i] == 'n')
			i++;
		if (tab[i] == '\0')
			return (1);
	}
	return (0);
}

static void		write_end(char **redplus, int fd, char **env, t_ms *ms)
{
	int		i;

	i = 0;
	if (ms->redplus != NULL)
	{
		while (redplus[i])
		{
			ft_treatment_instruct(redplus[i], fd, env, ms);
			if (redplus[i + 1] && ms->space != 1) //ajout de space pour pas d espace quand rien d afficher par la premiere commade, ex : $ljk
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
}

static void	deb_and_end(int fd, char **env, t_ms *ms, char *tab)
{
	char *str;

	str = find_deb(tab, '>');
	ft_treatment_instruct(str, fd, env, ms);
	if (ms->redplus)
		write_end(ms->redplus, fd, env, ms);
	free(str);

}

static void	parse_echo(char **tab, char **env, int fd, t_ms *ms)
{
	int		i;

	i = 1;
	while (tab[i] && flag_n(tab[i]) == 1)
		i++;
	while (tab[i])
	{
		if (ft_strchr(tab[i], '>') && no_back(tab[i], '>'))
		{
			deb_and_end(fd, env, ms, tab[i]);
			break ;
		}
		else if (tab[i][0] == '<')
		{
			if (!tab[i][1])
				i++;
		}
		else
		{
			ft_treatment_instruct(tab[i], fd, env, ms);
			if (tab[i + 1] && ms->space != 1 && !only_space(tab[i + 1], 0)) //ajout de space pour pas d espace quand rien d afficher par la premiere commade, ex : $ljk
				ft_putstr_fd(" ", fd);
		}
		i++;
	}
}

void		builtin_echo(char **tab, char **env, t_ms *ms)
{
	int		fd;
	int		flag;

	ms->space = 0; // dans init plutot ? et init en debut de boucle
	flag = 0;
	fd = find_fd(tab, ms);
	if (flag_n(tab[1]) == 1)
	{
		ms->flag = 1;
		flag = 1;
	}
	if (!tab[1])
		g_exit = 0;
	if (check_back(tab))
	{
		parse_echo(tab, env, fd, ms);
	}
	if (flag != 1)
		ft_putstr_fd("\n", fd);
}
