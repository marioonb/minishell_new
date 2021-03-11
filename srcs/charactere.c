/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charactere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 07:45:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/03/11 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*special_charactere(char *cmd, int fd)
{
	if (cmd[1])
	{
		if (cmd[1] == '#')
		{
			cmd++;
			ft_putchar_fd('0', fd);
		}
		else if (cmd[1] == '=' || cmd[1] == '%' || cmd[1] == BACK_S)
			ft_putchar_fd(DOLLS, fd);
	}
	return (cmd);
}

int		echo_charactere(char c)
{
	if (c == '#' || c == '%' || c == '=' || c == BACK_S)
		return (1);
	return (0);
}

int		caractere_red(char *c)
{
	if (*c == '?' && !c[1])
		return (0);
	if (*c == '#' || *c == '&' || *c == '*' || *c == '.' || *c == '/')
		return (0);
	return (1);
}
