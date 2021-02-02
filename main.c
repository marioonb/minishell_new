#include "./include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	size_t	buf_size;
	char	*cmd;
	t_env	env;

	(void)ac;
	(void)av;
	buffer = NULL;
	buf_size = 2048;
	env.env = duplicate_env(envp);
	env.export = duplicate_env(envp);
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL)
		ft_error_malloc();
	write(1, "$> ", 3);
	while (getline(&buffer, &buf_size, stdin) > 0)
	{
		cmd = ft_strtrim(buffer, "\n\t");
		ft_read_buffer(cmd, &env);
		write(1, "$> ", 2);
		free(cmd);
	}
	free(buffer);
	//system("leaks ./minishell");
}
