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

void	builtin_echo(char **tab, char **env, t_exit *exit) // 31 lignes
{
	int		i;
	int		fd;
	int		flag;
	int		x;

	//printf("%d\n", exit->exit);
//	int space;
//	space = 1;  // si ca a ecrit quelque chose ca reste a 1 sinon ca passe a 0;
	x = 0;
	i = 1;
	flag = 0;
	fd = find_fd(tab);
	if (flag_n(tab[i]) == 1)
		flag = 1;
	while (tab[i])
	{
		if (flag_n(tab[i]) == 1 && x != 1)
			i++;
		else if (tab[i][0] == '>')
			break ;
		else
		{
//			space = ft_essai(tab[i], fd, env);
			ft_treatment_instruct(tab[i], fd, env, exit);
			x = 1;
			if (tab[i + 1]) //&& space == 1)
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
	if (flag != 1)
		ft_putstr_fd("\n", fd);
	exit->exit = 0;
}
