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

int	execute_no_pipe(char *tab, t_env *env, t_ms *ms)
{
	char	 **tab_cmd;

	tab_cmd = ft_split_space(tab, SPACE);
	if (!(check_error_quotes1(tab_cmd, ms)))
		return (0);
	tab_cmd[0] = modif_commande_quote(tab_cmd[0]);
	if (is_builtin(tab_cmd[0]) == 1)
		find_builtin(tab_cmd, env, ms);
	else
	{
		if (get_path(tab_cmd, env) == 1)
			exec_cmd_shell(tab_cmd, env);
		else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
	}
	return (1) ;
}





// DUP = copie du fd
// dup2(oldfd, newfd)
// dup2() transforme newfd en une copie de oldfd, fermant auparavant newfd si besoin.
//créer un pipe avec fdp (entree et sortie), fork, dup 2
//écriture dans le pipe
//fermeture des pipes
// donner l'entrée à la prochaine commande.



void reset_fd(t_ms *ms)
{
   dup2(ms->in, 0);
    dup2(ms->out, 1);
    dup2(ms->err, 2);
}


// CELUI LA
void	open_process_pipe(char **cmd, t_env *env, t_ms *ms)
{
	pid_t		pid;

	pipe(ms->fdp);
	pid = fork();
	if (pid < 0)
		exit(-1);
	if (pid == 0)
	{
		if(ms->pipebef > 0) // si une commande avant bef est a 1
		{
			dup2(ms->caca, 0);
			close(ms->caca);
		}
		if (ms->pipe > 0) // si ya une comande apres, pipe n est toujours pas a 0
			dup2(ms->fdp[1], 1);
		if (is_builtin(cmd[0]) == 1)
			find_builtin(cmd, env, ms);
		else
		{
			if (get_path(cmd, env) == 1)
				exec_cmd_shell(cmd, env);
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
	waitpid(-1, &pid, 0);
	if (WIFEXITED(pid))
		ms->exit = WEXITSTATUS(pid);
	// on stoque le fd d'entrée (lecture) du processus pere dans lequel il y a tout ce qu'a écrit le fils. on va pouvoir le filer à (1)
	ms->caca = dup(ms->fdp[0]);
	close(ms->fdp[0]);
	close(ms->fdp[1]);
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

int execute_pipe(char *tab, t_env *env, t_ms *ms)
{
	ms->exit = 0;

	char **tab_cmd;
	int lenght;
	char **tab_cmd2;
	int i;
	i = 0;

	tab_cmd = ft_split_minishell(tab, PIPE);
	if (!(check_error_quotes1(tab_cmd, ms)))
		return (0);
	lenght = lenght_double_tab(tab_cmd);
	while (i < lenght) // sinon mettre pipe au lieu de lenght car pipe = nb de pipe + 1 donc nombre de commande
	{

			//mini_printf_fd(1, "%d\n\n", i);
			ms->pipe--;
			tab_cmd[i] =  ft_strtrim(tab_cmd[i], " ");  // trim les espace avant et apres a voir pour retirer
			//mini_printf_fd(1, "la chaine est %s", tab_cmd[i]);
			tab_cmd2 = ft_split_space(tab_cmd[i], ' ');		// split la commande passe de echo aaa à echo|aaa
			tab_cmd2[0] = modif_commande_quote(tab_cmd2[0]);
			//ft_read_tab_char(tab_cmd2);
		//	mini_printf_fd(2, "pipe = %d", ms->pipe);
		//	mini_printf_fd(2, "pipe bef = %d", ms->pipebef);
			open_process_pipe(tab_cmd2, env, ms);			// envoi la commande á process decoupée
			free_double_tab(tab_cmd2);						// free cette commade decoupee
			tab_cmd2 = NULL;
			ms->pipebef ++;
			i++;
	}
	free(tab_cmd);
	reset_fd(ms);
	ms->pipe = 0;
	//tab_cmd2 = NULL;
	//set readFDs
	//set writeFDs
	//set errorFDs
	return(1);
}

// NE PAS OUBLIER DE METTRE CA : 	tab_cmd[lenght] = modif_commande_quote(tab_cmd[0]); UNE FOIS AVOIR SPLIT SUR SPACE
