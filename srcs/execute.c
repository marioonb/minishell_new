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
			exec_cmd(tab_cmd, env);
		else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
	}
	return (1) ;
}


/*int open_process_pipe(char **tab_cmd, t_env *env, t_ms *ms)
{

	pid_t pid; // entree 0 sorti 1

	//ft_read_tab_char(tab_cmd);
	if (pipe(ms->fdp) < 0) // création du pipe entree et sortie
		exit (0);  // erreur de creation de pipe

	// creation du processus fils
	pid = fork();

	if (pid == -1)
		exit (0); //problemem de creation processus

	if (pid == 0) // on est dans le processus fils
	{
		//ms->pipe--;
			dup2(ms->fdp[1], STDOUT_FILENO);
		//if (ms->pipe == 1)
			//dup2(ms->fd, 0);
		close (ms->fdp[1]); // on ferme le fd d ecriture donc de sortie
		if (is_builtin(tab_cmd[0]) == 1)
			find_builtin(tab_cmd, env, ms);
		else
		{
			if (get_path(tab_cmd, env) == 1)
				exec_cmd(tab_cmd, env);
			else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
		}
		// Ici on va lire dans le descipteur fd[0]
		// read fd[0]
		// on le met dans une variable
		// on ecrit dans stdout
		// write (stdout);
	}
	else // on est dans le processus pere, il envoi au processus fils
	{
		// c est lui qui ecrit dans le descripteur de sortir fd [1]
		close (ms->fdp[0]); // il ferme donc le decripeur d entree avant d ecrire
		if (is_builtin(tab_cmd[0]) == 1)
			find_builtin(tab_cmd, env, ms);
		// Ici il ecrit
		// write fd[1]
		close(ms->fdp[1]);
		ms->fd = ms->fdp[0];
	}
	return(1);
}*/

/*int open_process_pipe(char **tab_cmd, t_env *env, t_ms *ms)
{

	pid_t pid; // entree 0 sorti 1
	ms->pipe--;
	//ft_read_tab_char(tab_cmd);
	if (pipe(ms->fdp) < 0) // création du pipe entree et sortie
		exit (0);  // erreur de creation de pipe

	// creation du processus fils
	pid = fork();

	if (pid == -1)
		exit (0); //problemem de creation processus

	if (ms->pipe == 0)
	{
		waitpid(pid, 0, 0);
	}
	if (pid > 0)
	{
		ft_putstr_fd("1 ICI ", 1);
		if (is_builtin(tab_cmd[0]) == 1)
			find_builtin(tab_cmd, env, ms);
		close(ms->fdp[1]);
		ms->fd = ms->fdp[0];
	}
	else
	{
		ft_putstr_fd("2 ICI ", 1);
		dup2(ms->fdp[1], 1);
		if (ms->pipe == 0)
		dup2(ms->fd, STDOUT_FILENO);

		close(ms->fdp[0]);
		if (is_builtin(tab_cmd[0]) == 1)
			find_builtin(tab_cmd, env, ms);
		else
		{
			if (get_path(tab_cmd, env) == 1)
				exec_cmd(tab_cmd, env);
			else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
		exit (ms->exit);
		}
	}
	return(1);
}*/


// DUP = copie du fd
// dup2(oldfd, newfd)
// dup2() transforme newfd en une copie de oldfd, fermant auparavant newfd si besoin.
//créer un pipe avec fdp (entree et sortie), fork, dup 2
//écriture dans le pipe
//fermeture des pipes
// donner l'entrée à la prochaine commande.

/*int open_process_pipe(char **tab_cmd, t_env *env, t_ms *ms)
{
	pid_t pid;
	int status = 0;
	pipe(ms->fdp);

	pid = fork();
	//mini_printf_fd(1, "pipe %d\n", ms->pipe);
	ms->pipe--;

	if (pid == -1)
		perror("fork");
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else if (pid == 0 && ms->pipe > 0)
	{
		dup2(ms->fdp[1], STDOUT_FILENO);
		if (is_builtin(tab_cmd[0]) == 1)
			find_builtin(tab_cmd, env, ms);
		else
		{
			if (get_path(tab_cmd, env) == 1)
				exec_cmd(tab_cmd, env);
			else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
		}
	}
	//pid = fork();
	else if (pid == 0 && ms->pipe == 0)
	{
		close(ms->fdp[1]);
		dup2(ms->fdp[0], STDIN_FILENO);
		if (is_builtin(tab_cmd[0]) == 1)
			find_builtin(tab_cmd, env, ms);
		else
		{
			if (get_path(tab_cmd, env) == 1)
				exec_cmd(tab_cmd, env);
			else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
		}
	}
	close(ms->fdp[0]);
	close(ms->fdp[1]);
	//ms->fd = 0;
	return(1);
}
*/
int open_process_pipe(char **tab_cmd, t_env *env, t_ms *ms)
{
	pid_t pid;
	int status = 0;
	pipe(ms->fdp);

	pid = fork();
	//mini_printf_fd(1, "pipe %d\n", ms->pipe);
	ms->pipe--;
	if (pid == 0 && ms->pipe > 0)
	{
		dup2(ms->fdp[1], STDOUT_FILENO);
		if (is_builtin(tab_cmd[0]) == 1)
			find_builtin(tab_cmd, env, ms);
		else
		{
			if (get_path(tab_cmd, env) == 1)
				exec_cmd(tab_cmd, env);
			else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
		}
	}
	pid = fork();
	if (pid == 0 && ms->pipe == 0)
	{
		close(ms->fdp[1]);
		dup2(ms->fdp[0], STDIN_FILENO);
		if (is_builtin(tab_cmd[0]) == 1)
			find_builtin(tab_cmd, env, ms);
		else
		{
			if (get_path(tab_cmd, env) == 1)
				exec_cmd(tab_cmd, env);
			else
			{
				ft_error(2, 127);
				ms->exit = 2;
			}
		}
	}
	close(ms->fdp[0]);
	close(ms->fdp[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	dup2(1, 1);
	dup2(0, 0);
	//ms->fd = 0;
	return(1);
}

int execute_pipe(char *tab, t_env *env, t_ms *ms)
{
	ms->exit = 0;
	ms->pid = 2;
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
			tab_cmd[i] =  ft_strtrim(tab_cmd[i], " ");  // trim les espace avant et apres a voir pour retirer
			//mini_printf_fd(1, "la chaine est %s", tab_cmd[i]);
			tab_cmd2 = ft_split_space(tab_cmd[i], ' ');		// split la commande passe de echo aaa à echo|aaa
			tab_cmd2[0] = modif_commande_quote(tab_cmd2[0]);
			//ft_read_tab_char(tab_cmd2);
			open_process_pipe(tab_cmd2, env, ms);			// envoi la commande á process decoupée
			free_double_tab(tab_cmd2);						// free cette commade decoupee
			tab_cmd2 = NULL;
			i++;
	}
	free(tab_cmd2);
	//tab_cmd2 = NULL;
	return(1);
}

// NE PAS OUBLIER DE METTRE CA : 	tab_cmd[lenght] = modif_commande_quote(tab_cmd[0]); UNE FOIS AVOIR SPLIT SUR SPACE
