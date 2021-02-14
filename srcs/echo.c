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

char	*find_var_doll(char *tab, int fd, char **env)
{
	char	*str_var;
	int		i;
	char	*str;

	str = NULL;
	str_var = NULL;
	i = 0;
	str_var = malloc(sizeof(char) * ft_strlen(tab) + 1);
	if (str_var == NULL)
		ft_error_malloc();
	while (check_caractere_name_var(*tab) == 1)
		str_var[i++] = *tab++;
	str_var[i] = '\0';
	if ((str = find_var(str_var, env)) != NULL)
		ft_out(str, fd);
	free(str_var);
	free(str);
	printf("tab est a %s", tab);
	return (tab);
}

int	flag_n(char *tab)
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
		else if (cmd[1] == '=' || cmd[1] == '%' || cmd[1] == BACK_S) // AJOUT DERNIER INS sinon marche pas : bash-3.2$ echo hallo$\USER
//hallo$USER
//bash-3.2$ echo hallo$\$USER
//hallo$$USER
//bash-3.2$
			ft_putchar_fd(DOLLS, fd);
	}
	return (cmd);
}

int	echo_charactere(char c)
{
	if (c == '#' || c == '%' || c == '=' || c == BACK_S) // AJOUT DERNIER INS sinon marche pas : bash-3.2$ echo hallo$\USER
//hallo$USER
//bash-3.2$ echo hallo$\$USER
//hallo$$USER
//bash-3.2$
		return (1);
	return (0);
}

void	parse_echo(char **tab, char **env, int fd, t_ms *ms)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	while (tab[i])
	{
		if (flag_n(tab[i]) == 1 && x != 1)
			i++;
		else if (tab[i][0] == '>')
			break ;
		else
		{
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
	//int		i;
	int		fd;
	int		flag;
	int		x;

	ms->space = 0; // dans init plutot ? et init en debut de boucle
	x = 0;
	//i = 1;
	flag = 0;
	fd = find_fd(tab);
	if (flag_n(tab[1]) == 1)
		flag = 1;
	if (!tab[1])
		ms->exit = 0;
	parse_echo(tab, env, fd, ms);
	if (flag != 1)
		ft_putstr_fd("\n", fd);
	//exit->exit = 0;
}
