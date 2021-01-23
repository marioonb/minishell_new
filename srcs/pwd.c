#include "../include/minishell.h"

void	builtin_pwd(char **tab, t_env *env)
{
	int		i;
	char	*cpy;
	int		fd;

	cpy = NULL;
	i = 0;
	fd = find_fd(tab);
	while (env->env[i])
	{
		cpy = ft_strstr(env->env[i], "PWD");
		if (cpy != NULL)
		{
			if (env->env[i][0] == 'P')
			{
				while (cpy[0] != '=')
					cpy++;
				cpy++;
				ft_out(cpy, fd);
			}
		}
		i++;
	}
	ft_putstr_fd("\n", fd);
}
