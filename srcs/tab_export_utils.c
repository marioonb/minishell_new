/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** la fonction est appelé pour changer le tableau export
** elle appelle une fonction pour creer un tableau avec la ligne supplementaire a ajouter
** elle appel une focntion pour le dupliquer et le mettre dans la structure
*/

void	change_export_add(char *tab, t_env *env)
{
	char	**new_export;

	new_export = replace_for_add(tab, env->export);
	free_tab_char(env->export);
	env->export = duplicate_tab_char(new_export);
	free_tab_char(new_export);
}

/*
** cette fonction cherche dans le tableau export
** si elle trouve le binaire envoyé
** elle remplace la ligne avec la nouvelle variable
*/

void	replace_var_export(char *bin, char *str, t_env *env)
{
	int	i;

	i = 0;
	while (env->export[i])
	{
		if (strncmp(bin, env->export[i], ft_strlen(bin)) == 0)
			env->export[i] = ft_strdup(str);
		i++;
	}
}

/*
** permet l'afficher du tableau export a l appel de la commande export seule
*/

void	declare_x(t_env *env, int fd)
{
	int		i;
	char	*bin;
	int		j;

	i = 0;
	while (env->export[i])
	{
		j = 0;
		while (env->export[i][j] != '\0' && env->export[i][j] != '=')
			j++;
		ft_putstr_fd("declare -x ", fd);
		bin = find_bin(env->export[i], '=', j);
		//ft_putstr_fd(bin, fd);
		if ((int)ft_strlen(env->export[i]) > (int)ft_strlen(bin))
		{
			ft_putstr_fd("=\"", fd);
			mini_printf_fd(fd, "%s", env->export[i], (int)ft_strlen(bin) + 1,
				(int)ft_strlen(env->export[i]));
			ft_putchar_fd('"', fd);
		}
		write(fd, "\n", 1);
		i++;
	}
	free(bin);
}
