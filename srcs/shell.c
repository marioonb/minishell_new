/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 07:45:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/03/11 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void			exec_cmd_shell(char **cmd, t_env *env)
{
	pid_t		pid;
	int			status;

	pid = 0;
	status = 0;
	if (cmd[0] == NULL)
		exit(1);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("error fork", 2);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, env->env) == -1)
			ft_putstr_fd("erreur execVe", 2);
		exit(EXIT_FAILURE);
	}
}

/*
** s_ifdir -> repertoire
** s_ifreg -> fichier ordinnaire
**s_ixusr -> proprietaire droit d execution
*/

static int		ft_verif_path(char *bin, int type)
{
	struct stat	mystat;

	errno = 0;
	stat(bin, &mystat);
	if (errno == 2 && type == 1)
		g_exit = ft_error_str(7, bin, 127);
	if (errno)
		return (1);
	if ((mystat.st_mode & S_IFMT) == S_IFDIR)
		g_exit = ft_error_str(5, bin, 126);
	if ((mystat.st_mode & S_IFMT) == S_IFREG)
	{
		if ((mystat.st_mode & S_IXUSR) == 0)
			g_exit = ft_error_str(6, bin, 126);
	}
	return (0);
}

static char		*check_tab_path(char **path_split, char *bin, char *cmd)
{
	int			i;

	i = 0;
	while (path_split[i])
	{
		bin = (char *)calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 +
			ft_strlen(cmd) + 1));
		if (bin == NULL)
			ft_error_malloc();
		ft_strcat(bin, path_split[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmd);
		if (ft_verif_path(bin, 2) != 1)
			break ;
		free(bin);
		bin = NULL;
		i++;
	}
	return (bin);
}

static char		*get_path_2(char *cmd, t_env *env)
{
	char		*path;
	char		**path_split;
	char		*bin;

	bin = NULL;
	path_split = NULL;
	path = NULL;
	path = find_var("PATH", env->env);
	if (path == NULL)
		return (NULL);
	path_split = ft_split(path, ':');
	free(path);
	path = NULL;
	bin = check_tab_path(path_split, bin, cmd);
	free_tab_char(path_split);
	return (bin);
}

int				get_path(char **cmd, t_env *env)
{
	char		*bin;

	g_exit = 0;
	bin = NULL;
	if (ft_strncmp(cmd[0], "./", 2) == 0 || cmd[0][0] == '/')
	{
		ft_verif_path(cmd[0], 1);
		return (1);
	}
	else if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		bin = get_path_2(cmd[0], env);
		if (bin == NULL)
		{
			g_exit = ft_error_str(4, cmd[0], 127);
			return (0);
		}
	}
	free(cmd[0]);
	cmd[0] = NULL;
	cmd[0] = ft_strdup(bin);
	free(bin);
	return (1);
}
