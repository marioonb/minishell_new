#include "../include/minishell.h"

char	*find_var_doll(char *tab, int fd, char **env)
{
	char	*str_var;
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	str_var = malloc(sizeof(char) * ft_strlen(tab) + 1);
	while (check_caractere_name_var(*tab) == 1)
		str_var[i++] = *tab++;
	str_var[i] = '\0';
	if ((str = find_var(str_var, env)) != NULL)
		ft_out(str, fd);
	free(str_var); // AJOUT +++++++++++++++++++++++++++++++
	free(str); ///////AJOUT ++++++++++++++++++++++++++++++++++++
	return (tab);
}

int	flag_n(char *tab)
{
	int		i;

	i = 0;
	if (tab == NULL)
		return(0);
	if (tab[i] == '-')
	{
		i++;
		if (tab[i] && tab[i] != 'n')
			ft_error_char(1, tab[i], 1);
		while (tab[i] && tab[i] == 'n')
			i++;
		if (tab[i] == '\0')
			return (1);
	}
	return (0);
}
char *special_charactere(char *cmd, int fd)
{
	if (cmd[1])
	{
		if (cmd[1] == '#')
		{
			cmd++;
			ft_putchar_fd('0', fd);
		}
		else if (cmd[1] == '=' || cmd[1] == '%' || cmd[1] ==  BACK_S) // AJOUT DERNIER INS sinon marche pas : bash-3.2$ echo hallo$\USER
//hallo$USER
//bash-3.2$ echo hallo$\$USER
//hallo$$USER
//bash-3.2$
			ft_putchar_fd(DOLLS, fd);
	}
	return(cmd);

}

int echo_charactere(char c)
{

	if (c == '#' || c == '%' || c == '=' || c == BACK_S) // AJOUT DERNIER INS sinon marche pas : bash-3.2$ echo hallo$\USER
//hallo$USER
//bash-3.2$ echo hallo$\$USER
//hallo$$USER
//bash-3.2$
		return(1);
	return(0);

}

char *simple_quote (char *cmd, int fd)
{
	int i;

	i = 0;
	cmd++;
	while (*cmd != SIMPLE_Q)
	{
		ft_putchar_fd(*cmd, fd);
		cmd++;
	}
	cmd++;
	return(cmd);
}

char	*dolls(char *cmd, int fd, char **env)
{
	if (cmd[1] && cmd[1] == '?')
		ft_putchar_fd('0', fd); // mettre la sortie plutot
	else if (cmd[1] && echo_charactere(cmd[1]))
			cmd = special_charactere(cmd, fd);
	else
	cmd ++;
	if (*cmd && (!ft_isalpha(*cmd) && *cmd != '_') && *cmd != DOUBLE_Q)
		cmd++;
	else
		cmd = find_var_doll(cmd, fd, env);
	return (cmd);
}

char	*backslash(char *cmd, int fd, char **env, int x)
{
	int cpt;
	int cpt2;

	cpt = 0;
	cpt2 = 0;
	while (*cmd && *cmd == BACK_S)
	{

		cpt++;
		cmd++;
	}
	cpt2 = cpt / 2;
	if ((*cmd && (*cmd!= DOLLS && *cmd != DOUBLE_Q && *cmd != ACCENT)) && x == 2)
		cpt2 = cpt2 + (cpt % 2);
	while (cpt2 > 0)
	{
		ft_putchar_fd(BACK_S, fd);
		cpt2--;
	}
	if (*cmd && *cmd == DOLLS)
	{
		if (cpt % 2 == 0)
		{
			cmd++;
			cmd = find_var_doll(cmd, fd, env);
		}
		else
		{
			ft_putchar_fd(DOLLS, fd);
			cmd++;
		}
	}
	else if (*cmd)  // ajout de if et (*cmd) sinon echo \\ marche pas
		{
			ft_putchar_fd(*cmd, fd);
			cmd++;
		}
	return(cmd);
}

char *double_quote(char *cmd, int fd, char **env)
{
	char *str =  NULL;
	int i;

	i = 0;

	printf("cmd 1 est a %s\n",cmd);
	cmd++;
	str = ft_strdup(cmd);
	printf("cmd 2 est a %s\n",cmd);
	while (*cmd && *cmd != DOUBLE_Q)
		{
			if (*cmd == BACK_S)
				{
					cmd++;
					i++;
				}
			i++;
			cmd++;
		}
	cmd++;
	str = ft_substr(str, 0, i);
	printf("cmd 3 est a %s\n", str);
	while (*str)
	{
		if (*str == DOLLS && str[1])
			str = dolls(str, fd, env);
		else if (*str == BACK_S)
			str = backslash(str, fd, env, 2);
		else
			{
				ft_putchar_fd(*str, fd);
				str++;
			}
	}
	//printf("cmd est a %s\n", str);
return (cmd);

}
void	ft_treatment_instruct(char *cmd, int fd, char **env)
{
	int x;

	x = 1;
	while (*cmd)
	{
		if (*cmd == DOUBLE_Q)
			cmd = double_quote(cmd, fd, env);
		else if (*cmd == SIMPLE_Q)
			cmd = simple_quote (cmd, fd);
		else if (*cmd == DOLLS && cmd[1])
				cmd = dolls(cmd, fd, env);
		else if (*cmd == BACK_S)
			cmd = backslash(cmd, fd, env, 1);
		else
		{
			printf("cmd c est quoi ? |%c|\n", cmd[0]);
			ft_putchar_fd(cmd[0], fd);
			cmd++;
		}
	}
}

void	builtin_echo(char **tab, char **env) // 31 lignes
{
	int		i;
	int		fd;
	int		flag;
	int		x;
//	int space;
//	space = 1;  // si ca a ecrit quelque chose ca reste a 1 sinon ca passe a 0;
	x = 0;
	i = 1;
	flag = 0;
	fd = find_fd(tab);
	if (flag_n(tab[i]) == 1)
		flag = 1;
	while (tab[i])
	{
		if (flag_n(tab[i]) == 1 && x != 1)
			i++;
		else if (tab[i][0] == '>')
			break ;
		else
		{
//			space = ft_essai(tab[i], fd, env);
			ft_treatment_instruct(tab[i], fd, env);
			x = 1;
			if (tab[i + 1]) //&& space == 1)
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
	if (flag != 1)
		ft_putstr_fd("\n", fd);
}
