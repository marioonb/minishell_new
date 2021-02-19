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
}

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	size_t	buf_size;
	char	*cmd;
	t_env	env;
	t_ms	ms;


	//env.enter = 1;
	ms.exit = 0;
	(void)ac;
	(void)av;
	buffer = NULL;
	buf_size = 2048;
	env.env = duplicate_tab_char(envp);
	env.export = duplicate_tab_char(envp);
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL)
		ft_error_malloc();
	write(2, "$> ", 3);
	ms.fd = 0;
	//while (getline(&buffer, &buf_size, stdin) > 0)
	while (get_next_line(1, &buffer) > 0)
	{
		init_fd(&ms);
		cmd = ft_strtrim(buffer, "\n\t");
		//mini_printf_fd(1, "EXIT avant = %d\n", exit.exit);
		ft_read_buffer(cmd, &env, &ms);
		//mini_printf_fd(1, "EXIT apres = %d\n", exit.exit);
		write(2, "$> ", 2);
		free(cmd);
	}
	free(buffer);
	//printf("fin");
	//exit (1);
	//system("leaks ./minishell");
	return(0);
}
