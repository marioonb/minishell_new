#include "../include/minishell.h"
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

/* fonction qui prend une string et qui verifie si un des termes de nos buildin y est present
* (ex : echo, pwd etc...) renvoi 1 si oui et 0 sinon
*/

int	is_builtin(char *cmd)
{
	int		i;
	char	*buil[8];

	i = 0;
	if (cmd == NULL)
		return (0);
	while (cmd && cmd[0] == ' ')
		cmd++;
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
		{ // voir a enlever pour la norme
			if (ft_strlen (cmd) > ft_strlen(buil[i]))
				return (0);
			return (1);
		} // voir a enlever pour la norme
		i++;
	}
	return (0);
}

int	find_pipe(char **tab)
{
	int	pipe;

	pipe = 0;
	while (*tab)
	{
		if (*tab[0] == PIPE)
			pipe ++;
		tab ++;
	}
	//printf ("pipe est a %d dans fonction\n", pipe);
	return (pipe);
}

/* cherche a quoi correspond tab[0], c est a dire la premiere instruction de la commande
* appel la fonction qui permet de traiter le builtin de la commande
* ne peux etre appelé que si la commade fait partie des commandes qu il fauut coder
*/

void	find_builtin (char **tab, t_env *env)
{
	env-> pipe = find_pipe(tab);
	//printf ("pipe est a %d\n", env->pipe);
	if (tab[0] == NULL)
		printf("error");
	else if (ft_strncmp(tab[0], "echo", ft_strlen(tab[0])) == 0)
		builtin_echo(tab, env->env);
	else if (ft_strncmp(tab[0], "pwd", ft_strlen(tab[0])) == 0)
		builtin_pwd(tab, env);
	else if (ft_strncmp(tab[0], "cd", ft_strlen(tab[0])) == 0)
		builtin_cd(tab, env);
	else if (ft_strncmp(tab[0], "export", ft_strlen(tab[0])) == 0)
		builtin_export(tab, env);
	else if (ft_strncmp(tab[0], "unset", ft_strlen(tab[0])) == 0)
		builtin_unset(tab, env);
	else if (ft_strncmp(tab[0], "env", ft_strlen(tab[0])) == 0)
		builtin_env(tab, env);
	else if (ft_strncmp(tab[0], "exit", ft_strlen(tab[0])) == 0)
		builtin_exit(tab);
}

/* permet l'affichage
* prend en compte le fd pour savoir ou la sortie doit se faire
* ecrit sur la sortie precisé
*/

void	ft_out(char *str, int fd)
{
	int	i;
	int	nb;
	int	compt;

	i = 0;
	nb = 0;
	compt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			while (str[i++] == '\\')
				compt ++;
			nb = compt / 2;
			while (nb-- > 0)
				write (fd, "\\", 1);
			i = i - 1;
		}
		else
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

/* cherche si dans la ligne de commande complete, il y a une redirection >
* si oui elle cherche le nom du fichier et creait ce fichier
* renvoi le type de fd a la fonction appelante
*/

int	find_fd(char **tab)
{
	int		fd;
	int		i;
	char	*files;

	files = NULL;
	fd = 1;
	i = 0;
	while (tab[i])
	{
		if (tab[i + 1] && ft_strchr(tab[i], '>'))
		{
			files = malloc (sizeof(char) * ft_strlen(tab[i + 1]) + 1);
			if (files == NULL)
				ft_error_malloc();
			ft_strncpy(files, tab[i + 1], ft_strlen(tab[i + 1]));
			fd = open(files, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666 );
			free(files); // AJOUT +++++++++++++++++++++++++++++++++++++++++++++
		}
		i++;
	}
	//printf("donne moi le fd = %d", fd);
	return (fd);
}
