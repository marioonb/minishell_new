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
	//printf("%d\n", exit->exit);
	if (cmd[1] && cmd[1] == '?')
		{
			mini_printf_fd(fd, "%d", ms->exit);
			cmd++;
		}
		//ft_putchar_fd('0', fd); // mettre la sortie plutot
	else if (cmd[1] && echo_charactere(cmd[1]))
		cmd = special_charactere(cmd, fd);
	else
		cmd ++;
	if (*cmd && (!ft_isalpha(*cmd) && *cmd != '_') && *cmd != DOUBLE_Q && *cmd != SIMPLE_Q)
		cmd++;
	else
		cmd = find_var_doll(cmd, fd, env);
		//printf("cmd est a %s\n", cmd);
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
		//printf("il passe dans la boucle 1 : \n");
		//printf("bcl 1 -> cpt est a : %d\n", cpt);
		//printf("bcl 1 -> cmd est a : %s\n", cmd);
		cpt++;
		cmd++;
		//printf("apres bcl 1 -> cpt est a : %d\n", cpt);
		//printf("apres bcl 1 -> cmd est a : %s\n", cmd);
	}
	cpt2 = cpt / 2;
	//printf("en divisant par 2 -> cpt2 est a : %d\n", cpt2);
	if ((*cmd && (*cmd != DOLLS && *cmd != DOUBLE_Q && *cmd != ACCENT))
		&& x == 2)
	{
		//printf("il passe dans le if\n");
		cpt2 = cpt2 + (cpt % 2);
		//printf("cpt2 devient : %d\n", cpt2);
	}
	while (cpt2 > 0)
	{
		//printf("il passe dans la boucle 2 : \n");
		//printf("il put un \\ : \n");
		ft_putchar_fd(BACK_S, fd);
		cpt2--;
	}
	if (!*cmd && cpt % 2 != 0) // si je fait exit-> exit = error, je devrai emporter exit et jai deja 4 param dans la fonction
		{
		 	ft_error(3, 0); // voir sinon pour envoye l exit, en elevant une autre variable... ou en la mettant en globale, et du coup retirer la condition dans le dernier else if
			return(NULL); // permet de recuperer la valeur null et mettre mexit a 2 mais avant si je remvoi null je segfault
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
		//printf("il passe dans le else if : \n");
		////printf("il put un %c : \n", *cmd);
		ft_putchar_fd(*cmd, fd);
		cmd++; // a remettre ??
	}
	//printf("il retourne cmd = %s\n", cmd);
	return (cmd);
}

char	*double_quote(char *cmd, int fd, char **env, t_ms *ms)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	//printf("cmd 1 est a %s\n",cmd);
	cmd++;
	str = ft_strdup(cmd);
	//printf("cmd 2 est a %s\n",cmd);
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
	//printf("cmd 3 est a %s\n", str);
	while (*str)
	{
		if (*str == DOLLS && str[1])
			str = dolls(str, fd, env, ms);
		else if (*str == BACK_S)
			{
				str = backslash(str, fd, env, 2);
				if (str == NULL) //je peux pas renvoyer null avec la fonction backslash car sinon ca segfault
				{	ms->exit = 2;
					//printf("PASSE LA ?");
					break ;
				}
			}
		else
		{
			ft_putchar_fd(*str, fd);
			str++;
		}
	}
	//free(str);
	//printf("cmd est a %s\n", str);
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
			if (cmd == NULL) // obligé si on veut mettre l erreur echo \\ a 2 mais le pb c est que si je renvoi null ca segfault
			{
				ms->exit = 2;
				break ;
			}
		}
		else
		{
			ft_putchar_fd(cmd[0], fd);
			cmd++;
		}
		ms->exit = 0;
	}
}
