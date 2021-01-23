#include "../include/minishell.h"

void	find_path(char **tab)
{
	if (tab[2])
		printf("trop d'arguments");
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
	//char	*path;

	oldpwd = NULL;
	pwd = NULL;
	//char	*pwd_ptr = NULL;
	//printf("juste pour la compil %c\n", tab[1][1]);
	find_path(tab);
	pwd = ft_strrchr(find_var("PWD=", env->env), '=') + 1;
	oldpwd = ft_strrchr(find_var("OLDPWD=", env->env), '=') + 1;
	if (!tab[1])
		pwd = ft_strrchr(find_var("HOME=", env->env), '=') + 1;
	//strcpy(env[11], "r");
	//chdir(tab[1]);
	//if (oldpwd != NULL && pwd != NULL)
	//	strcpy(oldpwd, pwd);
	//	if (pwd != NULL)
	//	{
	//		pwd = &pwd[-strlen("PWD=")];
	//		pwd_ptr = built_in_pwd();
	//		strcpy(pwd, pwd_ptr);
	//		free(pwd_ptr);
	//		pwd_ptr = NULL;
	//	}
	//}
	//else
	//	perror("chdir");
}
