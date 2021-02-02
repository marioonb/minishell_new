#include "../include/minishell.h"

char	*check_path(char **tab)
{
	int	i;

	i = 0;
	if (tab[2])
		ft_error(4, 1);
	if (tab[1][i] == '.')
		while (tab[1][i] == '.')
			i++;
	if (!tab[1][i])
	{
		if (i == 2)
			return ("JE NE SAIS PAS");
	}
	return (tab[1]);
}

/* recherche dans une chaine si un element de env s'y trouve
* si oui elle renvoi la ligen complete de env - le nom de varibqle jusqu'a =
* sinon elle renvoi NULL
*/

int	var_lenght (char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

char	*find_var(char *str, char **env)
{
	int	i;
	int	lenght;

	i = 0;
	while (env[i])
	{
		lenght = var_lenght(env[i]);
		//printf ("env[i] = %s pos %d\n", env[i], i);
		//printf("lenght est a = %d\n", lenght);
		//printf("env[i] avant boucle = %s\n", env[i]);
		//		if (ft_strncmp(str, env[i], (int)ft_strlen(str)) == 0)
		if (ft_strncmp(str, env[i], lenght) == 0
			&& (int)ft_strlen(str) <= lenght)
			return (ft_substr(env[i] + 1, lenght, ft_strlen(env[i]) - lenght));
		i++;
	}
	return (NULL);
}

/* recherche les path oldpwd et pwd et les modifie
*/

void	builtin_cd(char **tab, t_env *env)
{
	char	*oldpwd;
	char	*pwd;
	int		lenght;
	char	*pwd2;
	char	*oldpwd2;

	oldpwd2 = NULL;
	oldpwd = NULL;
	pwd = NULL;
	pwd2 = NULL;
	if (chdir(tab[1]) == 0)
	{
		if (!tab[1])
			pwd = find_var("HOME", env->env);
		else
		{
			pwd = check_path(tab);
			//pwd = strdup(tab[1]);
		}
		lenght = 4 + ft_strlen(pwd) + 1;
		pwd2 = malloc(sizeof(char) * (lenght));
		if (pwd2 == NULL)
			ft_error_malloc();
		ft_strncpy(pwd2, "PWD=", 5);
		ft_strlcat(pwd2, pwd, lenght);
		oldpwd = find_var("PWD", env->env);
		lenght = 7 + ft_strlen(oldpwd) + 1;
		oldpwd2 = malloc(sizeof(char) * (lenght));
		if (oldpwd2 == NULL)
			ft_error_malloc();
		ft_strncpy(oldpwd2, "OLDPWD=", 8);
		ft_strlcat(oldpwd2, oldpwd, lenght);
		treat_var(pwd2, env);
		treat_var(oldpwd2, env);
		free(oldpwd2);
		free(pwd2);
	}
	else
		ft_error_str(4, tab[1], 1);
}
