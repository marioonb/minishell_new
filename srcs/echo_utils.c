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

char	*simple_quote (char *cmd, int fd)
{
	int	i;

	i = 0;
	cmd++;
	while (*cmd && *cmd != SIMPLE_Q)
	{
		ft_putchar_fd(*cmd, fd);
		cmd++;
	}
	cmd++;
	return (cmd);
}

char	*dolls(char *cmd, int fd, char **env, t_ms *ms)
{
	if (cmd[1] && cmd[1] == '?')
	{
		mini_printf_fd(fd, "%d", g_exit);
		cmd++;
	}
	else if (cmd[1] && echo_charactere(cmd[1]))
		cmd = special_charactere(cmd, fd);
	else
		cmd ++;
	if (*cmd && (!ft_isalpha(*cmd) && *cmd != '_') && *cmd != DOUBLE_Q && *cmd != SIMPLE_Q)
		cmd++;
	else
		cmd = find_var_doll(cmd, fd, env);
	if (cmd[0] == '\0') // voir si ca pose pas de probleme ailleurs, mis pour que ca ne fasse pas d espace ici : echo $kjhjh salut
		ms->space = 1;
	return (cmd);
}

char	*backslash(char *cmd, int fd, char **env, int x)
{
	int	cpt;
	int	cpt2;

	cpt = 0;
	cpt2 = 0;
	while (*cmd && *cmd == BACK_S)
	{
		cpt++;
		cmd++;
	}
	cpt2 = cpt / 2;
	if ((*cmd && (*cmd != DOLLS && *cmd != DOUBLE_Q && *cmd != ACCENT))
		&& x == 2)
		cpt2 = cpt2 + (cpt % 2); // truc av
	while (cpt2 > 0)
	{
		ft_putchar_fd(BACK_S, fd);
		cpt2--;
	}
	if (*cmd && *cmd == DOLLS)
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
	}
	else if (*cmd && cpt % 2 != 0)
	{
		ft_putchar_fd(*cmd, fd);
		cmd++;
	}
	return (cmd);
}

// SI PROBLEME REMETTRE LA FONCTION PLUS BAS 16/02, FOMCTION DECOUPEE POUR LA NORME
void	double_quote2(char *str, int fd, char **env, t_ms *ms)
{
	while (*str)
	{
		if (*str == DOLLS && str[1])
			str = dolls(str, fd, env, ms);
		else if (*str == BACK_S) // truc av
			str = backslash(str, fd, env, 2);
		else
		{
			ft_putchar_fd(*str, fd);
			str++;
		}
	}
}

// SI PROBLEME, REMETTRE LA FONCTION PLUS BAS 16/02

char	*double_quote(char *cmd, int fd, char **env, t_ms *ms)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	cmd++;
	str = ft_strdup(cmd);
	while (*cmd && *cmd != DOUBLE_Q)
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

void	ft_treatment_instruct(char *cmd, int fd, char **env, t_ms *ms)
{
	while (*cmd)
	{
		if (*cmd == DOUBLE_Q)
			cmd = double_quote(cmd, fd, env, ms);
		else if (*cmd == SIMPLE_Q)
			cmd = simple_quote (cmd, fd);
		else if (*cmd == DOLLS && cmd[1])
			cmd = dolls(cmd, fd, env, ms);
		else if (*cmd == BACK_S)
		{
			cmd = backslash(cmd, fd, env, 1);
			//if (cmd == NULL) // obligé si on veut mettre l erreur echo \\ a 2 mais le pb c est que si je renvoi null ca segfault
			//{
			//	ft_error(1,1);
			//	g_exit = 2;
			//	break ;
			//}
		}
		else
		{
			ft_putchar_fd(cmd[0], fd);
			cmd++;
		}
		g_exit = 0;
	}
}

/* MARCHAIT, A METTRE A LA PLACE DE DOUBLE QUOTE ET DOUBLE QUOTE 2
char	*double_quote(char *cmd, int fd, char **env, t_ms *ms)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	cmd++;
	str = ft_strdup(cmd);
	while (*cmd && *cmd != DOUBLE_Q)
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
	while (*str)
	{
		if (*str == DOLLS && str[1])
			str = dolls(str, fd, env, ms);
		else if (*str == BACK_S)
		{
			str = backslash(str, fd, env, 2);
			if (str == NULL) //je peux pas renvoyer null avec la fonction backslash car sinon ca segfault
			{
				ms->exit = 2;
				break ;
			}
		}
		else
		{
			ft_putchar_fd(*str, fd);
			str++;
		}
	}
	return (cmd);
}*/
