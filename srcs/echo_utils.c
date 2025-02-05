/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*dolls(char *cmd, int fd, char **env, t_ms *ms)
{
	g_write = 1;
	if (cmd[1] && cmd[1] == '?')
	{
		mini_printf_fd(fd, "%d", g_exit);
		cmd++;
	}
	else if (cmd[1] && echo_charactere(cmd[1]))
		cmd = special_charactere(cmd, fd);
	else
		cmd++;
	if (*cmd && (!ft_isalpha(*cmd) && *cmd != '_') && *cmd != DBLE_Q &&
		*cmd != SIMPLE_Q)
	{
		cmd++;
		g_write = 0;
	}
	else
		cmd = find_var_doll(cmd, fd, env);
	if (cmd[0] == '\0' && g_write == 0)
		ms->space = 1;
	return (cmd);
}

char		*back_s(int cpt, char *cmd, int fd, char **env)
{
	if (cpt % 2 == 0)
	{
		cmd++;
		cmd = find_var_doll(cmd, fd, env);
	}
	else
	{
		ft_putchar_fd(DOLLS, fd);
		cmd++;
	}
	return (cmd);
}

char		*backslash(char *cmd, int fd, char **env, int x)
{
	int		cpt;
	int		cpt2;

	cpt = 0;
	cpt2 = 0;
	while (*cmd && *cmd == BACK_S)
	{
		cpt++;
		cmd++;
	}
	cpt2 = cpt / 2;
	if ((*cmd && (*cmd != DOLLS && *cmd != DBLE_Q && *cmd != ACCENT)) && x == 2)
		cpt2 = cpt2 + (cpt % 2);
	while (cpt2-- > 0)
		ft_putchar_fd(BACK_S, fd);
	if (*cmd && *cmd == DOLLS)
	{
		cmd = back_s(cpt, cmd, fd, env);
	}
	else if (*cmd && cpt % 2 != 0)
	{
		ft_putchar_fd(*cmd, fd);
		cmd++;
	}
	return (cmd);
}

static void	double_quote2(char *str, int fd, char **env, t_ms *ms)
{
	while (*str)
	{
		if (*str == DOLLS && str[1])
			str = dolls(str, fd, env, ms);
		else if (*str == BACK_S)
			str = backslash(str, fd, env, 2);
		else
		{
			ft_putchar_fd(*str, fd);
			str++;
		}
	}
}

char		*double_quote(char *cmd, int fd, char **env, t_ms *ms)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	cmd++;
	str = cmd;
	while (*cmd && *cmd != DBLE_Q)
	{
		if (*cmd == BACK_S)
		{
			cmd++;
			i++;
		}
		i++;
		cmd++;
	}
	cmd++;
	str = ft_substr(str, 0, i);
	double_quote2(str, fd, env, ms);
	free(str);
	return (cmd);
}
