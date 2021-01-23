/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:46:36 by mbelorge          #+#    #+#             */
/*   Updated: 2020/11/24 16:44:55 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim_char(char const *s1, char set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	a;

	i = 0;
	j = 0;
	a = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[j])
		j++;
	j--;
	if (s1[i] == set)
		i++;
	//if (i == ft_strlen(s1))
	//	return (ft_calloc(1, sizeof(char)));
	if (s1[j] == set)
		j--;
	if (!(str = ft_calloc(sizeof(char) * (j - i + 2), 2)))
		return (NULL);
	while (i <= j)
		str[a++] = s1[i++];
	str[a] = '\0';
	return ((char *)str);
}
