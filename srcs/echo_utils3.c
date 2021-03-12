/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 07:45:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/03/11 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*simple_quote(char *cmd, int fd)
{
	cmd++;
	while (*cmd && *cmd != SIMPLE_Q)
	{
		ft_putchar_fd(*cmd, fd);
		cmd++;
	}
	cmd++;
	return (cmd);
}

int		n(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_S)
			i = red_back(str, i, c);
		if (str[i] == c)
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}
