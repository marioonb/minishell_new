/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* Lit le buffer envoyé par l'utilisateur
*et separe chaque commande en double tableau de char
*/

int	empty(char *s)
{
	int cpt;

	cpt = 0;
	while (*s)
	{
		if (*s != ' ' && *s != ';' && *s != '|')
			return(1);
		if (*s == ';' || *s == '|')
			cpt++;
		s++;
	}
	if (cpt > 0)
		g_exit = ft_error(2, 2);
	return(0);
}

void	ft_read_buffer(char *buffer, t_env *env, t_ms *ms)
{
	char	**tab = NULL;
	int		i;

	i = 0;

	if (empty(buffer))
	{
		tab = ft_split_space(buffer, ';');
		while (tab[i])
		{
			ft_parse(tab[i], env, ms);
			i++;
		}
	free_tab_char(tab);}
}

void	exec_cmd_shell(char **cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	mini_printf_fd(2, "cmd[0] est a dddd%s\n", cmd[0]);
	//printf("RENTRE PAS DANS MES BUILTIN\n");
	if (cmd[0] == NULL)
		exit(1);
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		//printf("cmd[0] 22 est a %s", cmd[0]);
		if (execve(cmd[0], cmd, env->env) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

int	ft_verif_path(char *bin)
{
	struct stat	mystat;

	errno = 0;
	stat(bin, &mystat);
	if (errno)
		return (1);
	return (0);
}

/*
** Il s’agit des dossiers (séparer par ‘:‘) ou notre Shell va
**chercher notre binaire à exécuter.
**Nous devons maintenant écrire la fonction qui va concaténer
**notre path et le binaire.
**Il faut récupérer le contenu de la variable $PATH avec la fonction getenv.
**Elle prend un seul paramètre qui est la variable que l’on cherche et renvoie un pointeur sur le contenu de la variable passer en paramètre.
**Si notre binaire n’est dans aucun dossier, on peut avertir
**l’utilisateur par un Command not found, sinon on peut exécuter notre execve : D.
**La fonction qui récupère le contenue de la variable $PATH et
**qui renvoie le chemin absolu :
*/

char	*check_tab_path(char **path_split, char *bin, char *cmd)
{
	int	i;

	i = 0;
	while (path_split[i])
	{
		bin = (char *)calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(cmd) + 1));
		if (bin == NULL)
			ft_error_malloc();
		strcat(bin, path_split[i]);
		strcat(bin, "/");
		strcat(bin, cmd);
		if (ft_verif_path(bin) != 1)
			break ;
		free(bin);
		bin = NULL;
		i++;
	}
	return (bin);
}

int	get_path(char **cmd, t_env *env)
{
	char	*path;
	char	*bin;
	char	**path_split;

printf("commande de 0 est a [%s]xxxxxxx\n", cmd[0]);
	path = NULL;
	bin = NULL;
	path_split = NULL;
	if (!(ft_isalpha(cmd[0][0])))
		return(0);
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		path = find_var("PATH", env->env);
		if (path == NULL)
			return (0);
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		bin = check_tab_path(path_split, bin, cmd[0]);
		free_tab_char(path_split);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
	mini_printf_fd(2, "ICI");
		if (bin == NULL)
		return (0);
	else
		return (1);
}


















char	*modif_commande_quote(char *cmd)
{
	char	*str;
	int		c;

	str = NULL;
	if (cmd)
		str = strdup(cmd);
	if (str && (str[0] == DOUBLE_Q || str[0] == SIMPLE_Q))
	{
		c = str[0];
		str = ft_strtrim_char(str, c);
		ft_strncpy(cmd, str, ft_strlen(str)); // mis str a la fin au lieu de cmd dans ft_Strlen
	}
	free(str);
	return (cmd);
}

void	ft_parse(char *tab, t_env *env, t_ms *ms)
{
	ms->pipe = find_pipe(tab);
	if (ms->pipe > 0) // si pas de pipe pipe sera a zero
		ms->pipe++; // si il y en a au moins un, c est qui il a une cmd en plus, pipe est alors le nb de commande
	if (ms->pipe > 0)
		execute_pipe(tab, env, ms);
	else
		execute_no_pipe(tab, env, ms);
	//free_double_tab(tab_cmd); -> seg
}
