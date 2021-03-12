/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 07:45:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/03/11 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_treatment_instruct(char *cmd, int fd, char **env, t_ms *ms)
{
	while (*cmd)
	{
		if (*cmd == DBLE_Q)
			cmd = double_quote(cmd, fd, env, ms);
		else if (*cmd == SIMPLE_Q)
			cmd = simple_quote(cmd, fd);
		else if (*cmd == DOLLS && cmd[1])
			cmd = dolls(cmd, fd, env, ms);
		else if (*cmd == BACK_S)
			cmd = backslash(cmd, fd, env, 1);
		else
		{
			ft_putchar_fd(cmd[0], fd);
			cmd++;
		}
		g_exit = 0;
	}
}

static int	check_back2(char **tab, int i)
{
	int		j;
	int		cpt;

	cpt = 0;
	j = 0;
	while (tab[i][j])
	{
		if (tab[i][j] == BACK_S)
		{
			while (tab[i][j] && tab[i][j] == BACK_S)
			{
				cpt++;
				j++;
			}
			if (!tab[i + 1] && !tab[i][j] && cpt % 2 != 0)
			{
				g_exit = ft_error(3, 2);
				return (0);
			}
		}
		if (tab[i][j])
			j++;
	}
	return (1);
}

int			check_back(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (check_back2(tab, i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int			red_back(char *s, int i, char c)
{
	int		cpt;

	cpt = 0;
	while (s[i] == BACK_S)
	{
		i++;
		cpt++;
	}
	if (s[i] && s[i] == c && cpt % 2 != 0)
		i++;
	return (i);
}

char		*find_deb(char *str, char c)
{
	int		i;
	char	*res;
	char	d;

	res = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	while (str[i] && str[i] != c)
	{
		res[i] = str[i];
		if (str[i] == DBLE_Q || str[i] == SIMPLE_Q)
		{
			d = str[i];
			i++;
			while (str[i] && str[i] != d)
			{
				res[i] = str[i];
				i++;
			}
			res[i] = str[i];
		}
		if (str[i])
			i++;
	}
	res[i] = '\0';
	return (res);
}
