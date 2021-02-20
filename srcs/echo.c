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
		//if (tab[i] && tab[i] != 'n')
		//	ft_error_flag(tab[i]);
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
	//mini_printf_fd(2, "rentre dans write_end\n"); //
	if (ms->redplus != NULL)
	{
		while (redplus[i])
		{
			ft_treatment_instruct(redplus[i], fd, env, ms);
			//x = 1;
			if (redplus[i + 1] && ms->space != 1) //ajout de space pour pas d espace quand rien d afficher par la premiere commade, ex : $ljk
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
}

static void	parse_echo(char **tab, char **env, int fd, t_ms *ms)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	//mini_printf_fd(2, "rentre dans parse_echo\n"); //
	//while (tab[i])
	//if (flag_n(tab[i]) == 1 && x != 1)
	//		i++;
	//mini_printf_fd(2, "tab[[i] est a %s\n", tab[i]); //
	while (tab[i])
	{
		//mini_printf_fd(2, "rentre dans la boucle\n"); //
		if (flag_n(tab[i]) == 1 && x != 1)
			i++;
		else if (tab[i][0] == '>')
		{
			//mini_printf_fd(2, "rentre dans le chevron a break\n"); //
			write_end(ms->redplus, fd, env, ms);
			break ;
		}
		else if (tab[i][0] == '<')
		{
			if (tab[i][1])
				i++;
			else
				i = i + 2;
		}
		else
		{
			//mini_printf_fd(2, "rentre pour faire les instruct\n"); //
			ft_treatment_instruct(tab[i], fd, env, ms);
			x = 1;
			if (tab[i + 1] && ms->space != 1) //ajout de space pour pas d espace quand rien d afficher par la premiere commade, ex : $ljk
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
}

void	builtin_echo(char **tab, char **env, t_ms *ms)
{
	int		fd;
	int		flag;
	int		x;

	ms->space = 0; // dans init plutot ? et init en debut de boucle
	x = 0;
	flag = 0;
	fd = find_fd(tab, ms);
	if (flag_n(tab[1]) == 1)
		flag = 1;
	if (!tab[1])
		ms->exit = 0;
	parse_echo(tab, env, fd, ms);
	if (flag != 1)
		ft_putstr_fd("\n", fd);
	//exit->exit = 0;
}
