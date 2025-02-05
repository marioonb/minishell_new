/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** fonction qui prend une string et qui verifie si un des termes de nos buildin
** y est present
** (ex : echo, pwd etc...) renvoi 1 si oui et 0 sinon
*/

int			is_builtin(char *cmd)
{
	int		i;
	char	*buil[8];

	i = 0;
	if (cmd == NULL)
		return (0);
	buil[0] = "echo";
	buil[1] = "pwd";
	buil[2] = "export";
	buil[3] = "unset";
	buil[4] = "env";
	buil[5] = "exit";
	buil[6] = "cd";
	buil[7] = NULL;
	while (buil[i] && cmd)
	{
		if (!ft_strncmp(buil[i], cmd, ft_strlen(buil[i])))
		{
			if (ft_strlen(cmd) > ft_strlen(buil[i]))
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** cherche a quoi correspond tab[0],
** c est a dire la premiere instruction de la commande
** appel la fonction qui permet de traiter le builtin de la commande
** ne peux etre appelé que si la commade fait partie des commandes
** qu il fauut coder
*/

void		find_builtin(char **tab, t_env *env, t_ms *ms)
{
	ms->type = 1;
	if (ft_strncmp(tab[0], "echo", ft_strlen(tab[0])) == 0)
		builtin_echo(tab, env->env, ms);
	else if (ft_strncmp(tab[0], "pwd", ft_strlen(tab[0])) == 0)
		builtin_pwd(tab, env, ms);
	else if (ft_strncmp(tab[0], "cd", ft_strlen(tab[0])) == 0)
		builtin_cd(tab, env);
	else if (ft_strncmp(tab[0], "export", ft_strlen(tab[0])) == 0)
		builtin_export(tab, env, ms);
	else if (ft_strncmp(tab[0], "unset", ft_strlen(tab[0])) == 0)
		builtin_unset(tab, env);
	else if (ft_strncmp(tab[0], "env", ft_strlen(tab[0])) == 0)
		builtin_env(tab, env, ms);
	else if (ft_strncmp(tab[0], "exit", ft_strlen(tab[0])) == 0)
	{
		free_tab_char(env->env);
		free_tab_char(env->export);
		builtin_exit(tab);
	}
	free_tab_char(tab);
}

/*
** permet l'affichage
** prend en compte le fd pour savoir ou la sortie doit se faire
** ecrit sur la sortie precisé
*/

void		ft_out(char *str, int fd)
{
	int		i;
	int		nb;
	int		compt;

	i = 0;
	nb = 0;
	compt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			while (str[i++] == '\\')
				compt++;
			nb = compt / 2;
			while (nb-- > 0)
				write(fd, "\\", 1);
			i = i - 1;
		}
		else
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}
