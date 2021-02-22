/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_cmd(char **tab, t_env *env, t_ms *ms)
{
	char *cpy;

	cpy = tab[0]; //  pour renvoyer dans l'erreur car get_path supprime
	if (is_builtin(tab[0]) == 1)
		find_builtin(tab, env, ms);
	else
	{
		if (get_path(tab, env) == 1)
			exec_cmd_shell(tab, env);
		else
		{
			ft_error_str(4, cpy, 127);
			ms->exit = 2;
		}
	}
}

// a la fin ms->caca = dup(ms->fdp[0]);
// on stoque le fd d'entrée (lecture) du processus pere dans lequel
// il y a tout ce qu'a écrit le fils. on va pouvoir le filer à (1)

static void	open_process_pipe(char **cmd, t_env *env, t_ms *ms)
{
	pid_t	pid;

	pipe(ms->fdp);
	pid = fork();
	if (pid < 0)
		exit(-1);
	if (pid == 0)
	{
		if (ms->pipebef > 0) // si une commande avant bef est a 1
		{
			dup2(ms->caca, 0);
			close(ms->caca);
		}
		if (ms->pipe > 0) // si ya une comande apres, pipe n est toujours pas a 0
			dup2(ms->fdp[1], 1);
		exec_cmd(cmd, env, ms);
		close_pipe(ms);
		exit(errno);
	}
	waitpid(-1, &pid, 0);
	if (WIFEXITED(pid))
		ms->exit = WEXITSTATUS(pid);
	ms->caca = dup(ms->fdp[0]);
	close_pipe(ms);
}

int	execute_no_pipe(char *tab, t_env *env, t_ms *ms)
{
	char	**tab_cmd;

	tab_cmd = ft_split_space(tab, SPACE);
	if (!(check_error_quotes1(tab_cmd, ms)))
		return (0);
	tab_cmd[0] = modif_commande_quote(tab_cmd[0]);
	exec_cmd(tab_cmd, env, ms);
	free_tab_char(tab_cmd);
	return (1);
}

// DUP = copie du fd
// dup2(oldfd, newfd)
// dup2() transforme newfd en une copie de oldfd,
// fermant auparavant newfd si besoin.
//créer un pipe avec fdp (entree et sortie), fork, dup 2
//écriture dans le pipe
//fermeture des pipes
// donner l'entrée à la prochaine commande.

int	execute_pipe(char *tab, t_env *env, t_ms *ms)
{
	char	**tab_cmd;
	char	**tab_cmd2;
	int		i;

	i = 0;
	ms->exit = 0;
	tab_cmd = ft_split_minishell(tab, PIPE);
	if (!(check_error_quotes1(tab_cmd, ms)))
		return (0);
	while (ms->pipe > 0)
	{
		ms->pipe--;
		//tab_cmd[i] = ft_strtrim(tab_cmd[i], " ");// trim les espaces avant et apres, à retirer ?
		tab_cmd2 = ft_split_space(tab_cmd[i], ' ');
		tab_cmd2[0] = modif_commande_quote(tab_cmd2[0]);
		open_process_pipe(tab_cmd2, env, ms); // envoi la commade découpée
		free_tab_char(tab_cmd2); // free cette commade decoupee, a voir si pas free dans exec_cmd
		tab_cmd2 = NULL;
		ms->pipebef++;
		i++;
	}
	free(tab_cmd);
	reset_fd(ms);
	ms->pipe = 0;
	return (1);
}

/*void	open_process_pipe(char **cmd, t_env *env, t_ms *ms)
{

    pid_t		pid;

    pipe(ms->fdp);
    pid = fork();
	pid = fork();

	if (pid > 0)
	{
		waitpid(-1, &pid, 0);
		//kill(pid, SIGTERM);
	}
	else
	{
		if(ms->pipebef > 0)
		{
			dup2(ms->caca, 0);
			close(ms->caca);
		}
		if (ms->pipe > 0)
			dup2(ms->fdp[1], 1);
		if (is_builtin(cmd[0]) == 1)
			find_builtin(cmd, env, ms);
		else
		{
			if (get_path(cmd, env) == 1)
				exec_cmd(cmd, env);
			else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
		}
		close(ms->fdp[0]);
		close(ms->fdp[1]);
		exit(errno);
	}
	if (WIFEXITED(pid))
        ms->exit = WEXITSTATUS(pid);
	ms->caca = dup(ms->fdp[0]);
	close(ms->fdp[0]);
    close(ms->fdp[1]);
}*/
