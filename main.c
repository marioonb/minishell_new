/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void init_fd(t_ms *ms)
{
    ms->in = dup(STDIN_FILENO);
    ms->out = dup(STDOUT_FILENO);
    ms->err = dup(STDERR_FILENO);
	ms->pipebef = 0;
	ms->pipe = 0;
	ms->caca = 1;
	ms->red = 0;
	ms->redplus = NULL;
	ms->quote = 1;
}

// faire une globale pour exit, car on peut rien envoyer en parametre

void	sighandler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		printf("\n");
		g_exit = 130;
		mini_printf_fd(2, "" PINK "%s" SET"", "minishell $> ");
	}
	return ;
}

// voir pour retirer buff size, gnl protégé

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	char	*cmd;
	t_env	env;
	t_ms	ms;

	g_exit = 0;
	(void)ac;
	(void)av;
	buffer = NULL;
	env.env = duplicate_tab_char(envp);
	env.export = duplicate_tab_char(envp);
	buffer = (char *)calloc(sizeof(char), 15);
	if (buffer == NULL)
		ft_error_malloc();
	mini_printf_fd(2, "" PINK "%s" SET"", "minishell $> ");
	ms.fd = 0;
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	//while (getline(&buffer, &buf_size, stdin) > 0)
	while (get_next_line(1, &buffer) > 0)
	{
		init_fd(&ms);
		cmd = ft_strtrim(buffer, "\n\t");
		ft_read_buffer(cmd, &env, &ms);
		mini_printf_fd(2, "" PINK "%s" SET"", "minishell $> ");
		free(cmd);
		free(buffer);
	}
	free(buffer);
	free_tab_char(env.env);
	free_tab_char(env.export);
	free(ms.redplus);
	//system("leaks ./minishell");
	return(0);
}
