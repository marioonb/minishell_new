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

char	*special_charactere(char *cmd, int fd)
{
	if (cmd[1])
	{
		if (cmd[1] == '#')
		{
			cmd++;
			ft_putchar_fd('0', fd);
		}
		else if (cmd[1] == '=' || cmd[1] == '%' || cmd[1] == BACK_S) // AJOUT DERNIER INS sinon marche pas : TEST X
			ft_putchar_fd(DOLLS, fd);
	}
	return (cmd);
}

int	echo_charactere(char c)
{
	if (c == '#' || c == '%' || c == '=' || c == BACK_S) // AJOUT DERNIER INS sinon marche pas : TEST X
		return (1);
	return (0);
}

void	write_end(char **redplus, int fd, char **env, t_ms *ms)
{
	int	i;

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

int red_back(char *s, int i, char c)
{
	int cpt = 0;

	while (s[i] == BACK_S)
	{
		i++;
		cpt++;
	}
	//if (s[i] && (s[i] == '>' || s[i] == '<') && cpt%2 != 0)
	if (s[i] && s[i] == c && cpt%2 != 0)
		i++;
	return (i);
}

char *find_deb(char *str, char c)
{
	int i;
	char *res;

	res = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while (str[i] != c)
	{
			res[i] =  str[i];
			i++;
	}
	res[i] = '\0';
	return (res);
}

int no_back(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_S)
			i = red_back(str, i, '>');
		if (str[i] == '>')
			return(1);
		if (str[i])
			i++;
	}
	return(0);


}

static void	parse_echo(char **tab, char **env, int fd, t_ms *ms)
{
	int	i;
	char *str;

	i = 1;
	while (tab[i] && flag_n(tab[i]) == 1 )
			i++;
	while (tab[i])
	{
		if (strchr(tab[i], '>') && no_back(tab[i]))
		{
			str = find_deb(tab[i], '>');
			ft_treatment_instruct(str, fd, env, ms);
			if (ms->redplus)
				write_end(ms->redplus, fd, env, ms);
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

int check_back(char **tab)
{
	int i;
	int j;

	int cpt = 0;
	i = 0;
	while (tab[i])
	{
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
				if (!tab[i+1] && !tab[i][j] && cpt % 2 != 0)
				{
					g_exit = ft_error(3, 2);
					return(0);
				}
			}
			if(tab[i][j])
				j++;
		}
		i++;
	}return(1);
}

void	builtin_echo(char **tab, char **env, t_ms *ms)
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
