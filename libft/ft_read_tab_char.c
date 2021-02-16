/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_tab_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** affiche un double tableau de char
*/

void	ft_read_tab_char(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i] != NULL)
	{
		while (tab[i][j] != '\0')
		{
			printf("|%c|", tab[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}
