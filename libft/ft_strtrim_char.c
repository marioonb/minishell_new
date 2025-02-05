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
	if (s1[j] == set)
		j--;
	str = ft_calloc(sizeof(char) * (j - i + 2), 2);
	if (!str)
		return (NULL);
	while (i <= j)
		str[a++] = s1[i++];
	str[a] = '\0';
	return ((char *)str);
}
