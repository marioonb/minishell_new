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

int execute_no_pipe(char *tab, t_env *env, t_ms *ms)
{
	char	 **tab_cmd;

	tab_cmd = ft_split_space(tab, SPACE);
	if (!(check_error_quotes1(tab_cmd, ms)))
		return (0);
	//ft_read_tab_char(tab_cmd);
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
	return(1) ;
}


/*void open_process_pipe(tab_cmd, t_ms *ms)
{
	if (pipe(ms->fdp) == -1)
	{
		printf("pipe failed\n");
		return 1;
	}

	// create the child
	int  pid;
	if ((pid = fork()) < 0)
     {
       printf("fork failed\n");
       return 2;
     }

   if (pid == 0)
     {
       // child
       char buffer[BUFSIZ];

       close(ms->pfd[1]); // close write side

       // read some data and print the result on screen
       while (read(ms->pfd[0], buffer, BUFSIZ) != 0)
         printf("child reads %s", buffer);

       close(ms->pfd[0]); // close the pipe
     }
   else
     {
       // parent
       char buffer[BUFSIZ];

       close(ms->pfd[0]); // close read side

       // send some data into the pipe
       strcpy(buffer, "HelloWorld\n");
       write(ms->pfd[1], buffer, strlen(buffer)+1);

       close(ms->pfd[1]); // close the pipe
     }

   return 0;
}
*/

int execute_pipe(char *tab, t_ms *ms)
{

	ms->exit = 0;
	ms->pid = 2;
	char **tab_cmd;
	int lenght;

	tab_cmd = ft_split_minishell(tab, PIPE);
	lenght = lenght_double_tab(tab_cmd);
	while (lenght >= 0)
	{
			tab_cmd[lenght] =  ft_strtrim(tab_cmd[lenght], " ");
			//open_process_pipe(tab_cmd, env);
	}
	ft_read_tab_char(tab_cmd);
	return(0);
}

