#include "../include/minishell.h"

/*
** call find_fd to know the type of output.
** call ft_out for write env line by line
*/

void	builtin_env(char **tab, t_env *env)
{
	int	fd;
	int	i;

	i = 0;
	fd = find_fd(tab);
	if (tab[1])
		ft_error_str(2, tab[1], 127);
	while (env->env[i])
	{
		ft_out(env->env[i], fd);
		write(fd, "\n", 1);
		i++;
	}
}
