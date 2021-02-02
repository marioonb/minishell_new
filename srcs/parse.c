#include "../include/minishell.h"
#include <stdbool.h>

/*
* Lit le buffer envoyé par l'utilisateur
*et separe chaque commande en double tableau de char
*/

void	ft_read_buffer(char *buffer, t_env *env)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split_minishell(buffer, ';');
	while (tab[i])
	{
		ft_parse(tab[i], env);
		i++;
	}
	free_double_tab(tab);
}

////////////////////////////////////////////////////////////////111111//

static void	exec_cmd(char **cmd, t_env *env)						////
{																	////
	pid_t	pid;													////
	int		status;													////
																	////
	pid = 0;														////
	status = 0;														////
																	////
	//printf("RENTRE PAS DANS MES BUILTIN\n");						////
	pid = fork();													////
	if (pid == -1)													////
		perror("fork");												////
	else if (pid > 0)												////
	{																////
		waitpid(pid, &status, 0);									////
		kill(pid, SIGTERM);											////
	}																////
	else															////
	{																////
		if (execve(cmd[0], cmd, env->env) == -1)					////
			perror("shell");										////
		exit(EXIT_FAILURE);											////
	}																////
}																	////
																	////
static bool	get_absolute_path(char **cmd, t_env *env)				////
{																	////
	char	*path;													////
	char	*bin;													////
	char	**path_split;											////
	size_t	idx;													////
																	////
	path = NULL;													////
	bin = NULL;														////
	path_split = NULL;												////
	idx = 0;														////
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)			////
	{																////
		for (int i = 0; env->env[i]; i++)							////
		{															////
			if (!strncmp(env->env[i], "PATH=", 5))					////
			{														////
				path = strdup(&env->env[i][5]);						////
				break ;												////
			}														////
		}															////
		if (path == NULL)											////
			return (false);											////
		path_split = ft_split(path, ':');							////  *****************
		free(path);													////
		path = NULL;												////
		for (idx = 0; path_split[idx]; idx++)						////
		{															////
			bin = (char *)calloc(sizeof(char), (strlen(path_split[idx]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)										////
				break ;												////
			strcat(bin, path_split[idx]);							////
			strcat(bin, "/");										////
			strcat(bin, cmd[0]);									////
			if (access(bin, F_OK) == 0)								////
				break ;												////
			free(bin);												////
			bin = NULL;												////
		}															////
		free_double_tab(path_split);										////
		free(cmd[0]);												////
		cmd[0] = bin;												////
	}																////
	else															////
	{																////
		free(path);													////
		path = NULL;												////
	}																////
	return (bin == NULL ? false : true);							////
}																	////
																	////
////////////////////////////////////////////////////////////////2222222/

char	**modif_commande_quote(char **cmd)
{
	char	*str;
	int		c;

	str = NULL;
	str = strdup(cmd[0]);
	if (str[0] == DOUBLE_Q || str[0] == SIMPLE_Q)
	{
		c = str[0];
		str = ft_strtrim_char(str, c);
		cmd[0] = str;
		printf("str est a %s\n", str);
	}
	free(str);
	return (cmd);
}

void	ft_parse(char *tab, t_env *env)
{
	char	**tab_cmd;

	tab_cmd = ft_split_space(tab, SPACE);
	//ft_read_tab_char(tab_cmd);
	check_error_quotes1(tab_cmd);
	tab_cmd = modif_commande_quote(tab_cmd);
	if (is_builtin(tab_cmd[0]) == 1)
		find_builtin(tab_cmd, env);
	else
	{
//////////////////////////////////////////////////////////////1111111///
		if (get_absolute_path(tab_cmd, env) == true)				////
			exec_cmd(tab_cmd, env);									////
		else														////
			fprintf(stderr, "Command not found\n");					////
//////////////////////////////////////////////////////////////////222222
	}
	//free_double_tab(tab_cmd); -> seg
}
