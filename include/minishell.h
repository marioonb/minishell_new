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

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>

# define DOUBLE_Q '"'
# define SIMPLE_Q '\''
# define BACK_S '\\'
# define DOLLS '$'
# define ACCENT '`'
# define PIPE '|'
# define SPACE ' '
# define PINK "\033[35;01m"
# define RED "\033[31;01m"
# define SET "\033[00m"

typedef struct	s_env
{
	char		**env;
	char		**export;
}				t_env;

typedef struct	s_ms
{
	int			pipe;
	int			pipebef;
	pid_t		pid;
	int			status;
	char		**enter;
	int			fd;
	int			flag;
	int			fdp[2];
	int			quote;
	int			space;
	int			res;
	int			in;
	int			out;
	int			err;
	int			red;
	char		**redplus;
}				t_ms;

int		g_exit;
int		g_write;

int				is_builtin(char *cmd);
void			find_builtin (char **tab, t_env *env, t_ms *ms);
void			ft_out(char *str, int fd);
char			*check_path(char **tab);
int				builtin_cd(char **tab, t_env *env);
char			*special_charactere(char *cmd, int fd);
int				echo_charactere(char c);
int				caractere_red(char *c);
int				check_error_quotes1(char **tab, t_ms *ms);
char			*simple_quote (char *cmd, int fd);
char			*dolls(char *cmd, int fd, char **env, t_ms *ms);
char			*backslash(char *cmd, int fd, char **env, int x);
char			*double_quote(char *cmd, int fd, char **env, t_ms *ms);
void			ft_treatment_instruct(char *cmd, int fd, char **env, t_ms *ms);
int				check_back(char **tab);
int				red_back(char *s, int i, char c);
char			*find_deb(char *str, char c);
int				no_back(char *str, char c);
void			builtin_echo(char **tab, char **env, t_ms *ms);
void			builtin_env(char **tab, t_env *env, t_ms *ms);
int				execute_no_pipe(char *tab, t_env *env, t_ms *ms);
int				execute_pipe(char *tab, t_env *env, t_ms *ms);
void			builtin_exit(char **tab);
void			treat_var(char *str, t_env *env);
void			builtin_export(char **tab, t_env *env, t_ms *ms);
void			reset_fd(t_ms *ms);
void			close_pipe(t_ms *ms);
void			ft_error_malloc(void);
void			ft_error_exit (int a, char *s, int nexit);
int				ft_error(int a, int nexit);
int				ft_error_str(int a, char *s, int nexit);
int				ft_error_char(int a, int nexit, char c);
void			ft_read_buffer(char *buffer, t_env *env, t_ms *ms);
void			ft_parse(char *tab, t_env *env, t_ms *exit);
int				find_pipe(char *tab);
void			builtin_pwd(char **tab, t_env *env, t_ms *ms);
char			**duplicate_end(char **tab, int i);
int				only_chevron(char *str, t_ms *ms, char c);
int				find_fd(char **tab, t_ms *ms);
int				get_path(char **cmd, t_env *env);
void			exec_cmd_shell(char **cmd, t_env *env);
char			**ft_split_space(char *s, char c);
void			change_env_add (char *tab, t_env *env);
void			replace_var_env(char *bin, char *str, t_env *env);
char			**replace_for_add(char *str, char **env);
void			change_export_add(char *tab, t_env *env);
void			replace_var_export(char *bin, char *str, t_env *env);
void			declare_x(t_env *env, int fd);
void			builtin_unset(char **tab, t_env *env);
int				search_doll(char *s);
char			*find_var_doll(char *tab, int fd, char **env);
int				check_caractere_name_var(char c);
void			check_name_var(char *str);
char			*find_bin(char *str, char c, int a);
int				var_lenght (char *str);
char			*find_var(char *str, char **env);
int				only_space(char *tab, int i);
int				empty(char *s);
char			*modif_commande_quote(char *cmd);

#endif
