/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** call find_fd to know the type of output.
** call ft_out for write env line by line
*/

void	builtin_env(char **tab, t_env *env, t_exit *exit)
{
	int	fd;
	int	i;

	i = 0;
	fd = find_fd(tab);
	if (tab[1])
		exit->exit = ft_error_str(2, tab[1], 127);
	else
	{
		while (env->env[i])
		{
			ft_out(env->env[i], fd);
			write(fd, "\n", 1);
			i++;
		}
	}
}
