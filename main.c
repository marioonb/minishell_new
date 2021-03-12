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

void		init_fd(t_ms *ms)
{
	ms->in = dup(STDIN_FILENO);
	ms->out = dup(STDOUT_FILENO);
	ms->err = dup(STDERR_FILENO);
	ms->pipebef = 0;
	ms->pipe = 0;
	ms->res = 1;
	ms->red = 0;
	ms->redplus = NULL;
	ms->quote = 1;
	ms->flag = 0;
	ms->type = 0;
}

void		sighandler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		mini_printf_fd(2, "\n");
		g_exit = 130;
		mini_printf_fd(2, "" PINK "%s" SET"", "minishell $> ");
	}
	if (sig_num == SIGQUIT)
	{
		ft_putstr_fd("\033[1C", 2);
		ft_putstr_fd("\b\b \b\b \b\b", 2);
		ft_putstr_fd("\033[1C", 2);
	}
	return ;
}

void		free_end(t_env *env)
{
	if (env->env != NULL)
		free_tab_char(env->env);
	if (env->export != NULL)
		free_tab_char(env->export);
}

void		init(t_env *env, char **envp, t_ms *ms)
{
	env->env = duplicate_tab_char(envp);
	env->export = duplicate_tab_char(envp);
	ms->fd = 0;
	replace_var_env("SHLVL", "SHLVL=2", env);
	replace_var_export("SHLVL", "SHLVL=2", env);
}

int			main(int ac, char **av, char **envp)
{
	char	*buffer;
	char	*cmd;
	t_env	env;
	t_ms	ms;

	g_exit = 0;
	(void)ac;
	(void)av;
	buffer = NULL;
	init(&env, envp, &ms);
	mini_printf_fd(2, "" PINK "%s" SET"", "minishell $> ");
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	while (get_next_line(0, &buffer) > 0)
	{
		init_fd(&ms);
		cmd = ft_strtrim(buffer, "\n\t");
		ft_read_buffer(cmd, &env, &ms);
		mini_printf_fd(2, "" PINK "%s" SET"", "minishell $> ");
		free(cmd);
		free(buffer);
	}
	free(buffer);
	free_end(&env);
	return (0);
}
