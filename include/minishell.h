/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>

#include "../libft/libft.h"

#define	DOUBLE_Q '"'
#define	SIMPLE_Q '\''
#define	BACK_S '\\'
#define	DOLLS '$'
#define	ACCENT '`'
#define	PIPE '|'
#define	SPACE ' '
#define PINK "\033[35;01m"
#define RED "\033[31;01m"
#define SET "\033[00m"

typedef struct s_env
{
	char	**env;
	char	**export;
}				t_env;

typedef struct s_ms
{
	int		pipe;
	int		pipebef;
	pid_t	pid;
	int		status;
	char	**enter;
	int		fd;
	int		fdp[2];
	int		quote;
	int		space;
	int		caca;
	int		in;
    int 	out;
    int		err;
	int		red;
	char	**redplus;
}				t_ms;

int		g_exit;

// fonctions builtin
int		is_builtin(char *cmd);
int		find_pipe(char *tab);
void	find_builtin (char **tab, t_env *env, t_ms *ms);
void	ft_out(char *str, int fd);
int		find_fd(char **tab, t_ms *ms);

// fontions de cd + 2 static
char	*check_path(char **tab); //*
int		builtin_cd(char **tab, t_env *env);

// fonctions check_error + 2 statics
//int	check_error_quote(char *tab, int quote);
int		check_error_quotes1(char **tab, t_ms *ms);

// fonction echo + 2 static
char	*special_charactere(char *cmd, int fd);
int		echo_charactere(char c); //*
void	builtin_echo(char **tab, char **env, t_ms *ms);

// fonctions echo_utils
char	*simple_quote (char *cmd, int fd); //*
char	*dolls(char *cmd, int fd, char **env, t_ms *ms); //*
char	*backslash(char *cmd, int fd, char **env, int x); //*
char	*double_quote(char *cmd, int fd, char **env, t_ms *ms); //*
void	ft_treatment_instruct(char *cmd, int fd, char **env, t_ms *ms);

// fonction env
void	builtin_env(char **tab, t_env *env, t_ms *ms);

// fonctions execute + 2 static
int		execute_no_pipe(char *tab, t_env *env, t_ms *ms);
int		execute_pipe(char *tab, t_env *env, t_ms *ms);

// fonction exit + 1 static
void	builtin_exit(char **tab);

// fonctions export
void	treat_var(char *str, t_env *env);
void	builtin_export(char **tab, t_env *env, t_ms *ms);

// fonctions ft_error
void	ft_error_malloc(void);
void	ft_error_exit (int a, char *s, int nexit);
int		ft_error(int a, int nexit);
int		ft_error_str(int a, char *s, int nexit);
//void	ft_error_flag(char c);
int		ft_error_char(int a, int nexit, char c);

// fonctions parse
void	ft_read_buffer(char *buffer, t_env *env, t_ms *ms);
void	exec_cmd_shell(char **cmd, t_env *env);
char	*check_tab_path(char **path_split, char *bin, char *cmd);
int		get_path(char **cmd, t_env *env);
//bool	get_path(char **cmd, t_env *env);
char	*modif_commande_quote(char *cmd);
void	ft_parse(char *tab, t_env *env, t_ms *exit);

// fonction pwd
void	builtin_pwd(char **tab, t_env *env, t_ms *ms);

// split_minishell && split_space
char	**ft_split_minishell(char const *s, char c);
char	**ft_split_space(char const *s, char c);

// fonctions tav_env_utils
void	change_env_add (char *tab, t_env *env);
void	replace_var_env(char *bin, char *str, t_env *env);
char	**replace_for_add(char *str, char **env);


//fonctions tab_export_utils
void	change_export_add(char *tab, t_env *env);
void	replace_var_export(char *bin, char *str, t_env *env);
void	declare_x(t_env *env, int fd);


// fonctions unset + 3 static
void	builtin_unset(char **tab, t_env *env);


// fonctions utils_dolls
int		search_doll(char *s);
char	*find_var_doll(char *tab, int fd, char **env);

//fonction utils_environnement_var
char	*find_bin(char *str, char c, int a);
int		var_lenght (char *str); //*
char	*find_var(char *str, char **env);
int		check_caractere_name_var(char c);
void	check_name_var(char *str);

//fonction fd
void	reset_fd(t_ms *ms);
void	close_pipe(t_ms *ms);

int		check_back(char **tab);
//printf("pwd est %s\n", pwd);
//printf("pwd est %d\n", (int)ft_strlen(pwd));
//printf("lenght est donc a %d\n", lenght);
//printf("juste pour la compil %c\n", tab[1][1]);

int		red_back(char *s, int i, char c);
int no_back(char *str);
