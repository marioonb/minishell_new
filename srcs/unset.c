#include "../include/minishell.h"

// delete dans les 2 tableau

char	**delete_env_element(int j, char **env)
{
	char	**env_new;
	int		i;
	int		ligne;
	int		k;

	k = 0;
	ligne = 0;
	env_new = NULL;
	while (env[ligne] != NULL)
		ligne++;
	i = 0;
	env_new = malloc(sizeof(char*) * (ligne));
	if (!env_new)
		ft_error_malloc();
	while (i < ligne)
	{
		if (i != j)
		{
			env_new[k] = ft_strdup(env[i]);
			k++;
		}
		i++;
	}
	env_new[k] = NULL;
	return (env_new);
}

void	change_env_supp (int i, t_env *env)
{
	char	**new_env;

	new_env = delete_env_element(i, env->env);
	free_double_tab(env->env);
	env->env = duplicate_env(new_env);
	free_double_tab(new_env);
}

void	change_export_supp (int i, t_env *env)
{
	char	**new_export;

	new_export = delete_env_element(i, env->export);
	free_double_tab(env->export);
	env->export = duplicate_env(new_export);
	free_double_tab(new_export);
}

void	builtin_unset(char **tab, t_env *env)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (tab[j])
	{
		while (env->env[i])
		{
			if (ft_strncmp(tab[j], env->env[i], ft_strlen(tab[j])) == 0)
			{
				change_env_supp(i, env);
				break ;
			}
			i++;
		}
		i = 0;
		while (env->export[i])
		{
			if (ft_strncmp(tab[j], env->export[i], ft_strlen(tab[j])) == 0)
			{
				change_export_supp(i, env);
				break ;
			}
			i++;
		}
		j++;
	}
}
