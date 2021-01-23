# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
#include <signal.h>
#include <fcntl.h>

# include "../libft/libft.h"

#define DOUBLE_Q '"'
#define SIMPLE_Q '\''
#define BACK_S '\\'
#define DOLLS '$'

typedef struct	s_env
{
	char **env;
	char **export;

}				t_env;


void	ft_read_buffer(char *buffer, t_env *env);
void	ft_error(int a, int nexit);
void	ft_echo(char **tab);
void	free_double_tab(char **tab);
int		check_error_quote(char *tab, int quote);
void	check_error_quotes1(char **tab);
void	ft_read_tab_char(char **tab);
char	**modif_tab(char **cmd);
int		is_builtin(char *cmd);
void	ft_parse(char *tab, t_env *env);
void	find_builtin (char **tab, t_env *env);
void	builtin_echo(char **tab, char **env);
void	builtin_pwd(char **tab, t_env *env);
void	builtin_cd(char **tab, t_env *env);
void	builtin_export(char **tab, t_env *env);
void	builtin_unset(char **tab, t_env *env);
void	builtin_env(char ** tab, t_env *env);
void	builtin_exit(char **tab);
char	**duplicate_env(char **envp);
void	ft_out(char *str, int fd);
int		find_fd(char **tab);
//void	change_env (char *tab, t_env *env);
char	*find_var(char *str, char** env);
void	ft_error_char(int a, char c, int nexit);
char	**ft_split_minishell(char const *s, char c);
void	ft_error_str(int a, char *s, int nexit);
void	check_name_var(char *str);
int		check_caractere_name_var(char c);
char	**ft_split_space(char const *s, char c);
void	change_export_add(char *tab, t_env *env);
void	replace_var_export(char *bin, char *str, t_env *env);
void	declare_x(char **tab, t_env *env);
void	change_env_add (char *tab, t_env *env);
void	replace_var_env(char *bin, char *str, t_env *env);
char	*find_bin(char *str, char c, int a);
char	**replace_for_add(char *str, char **env);
