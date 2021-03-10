/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	for_the_norm(char *s, int i)
{
	char	d;

	d = s[i];
	if (i > 0 && s[i - 1] == '\\')
		i++;
	else
	{
		i++;
		while (s[i] && s[i] != d)
		{
			if (s[i] == '\\' && d != SIMPLE_Q)
				i++;
			if (s[i])
				i++;
		}
		if (s[i] && s[i] == d)
			i++;
	}
	return (i);
}

int			split_back(char *s, int i, char c)
{
	int		cpt;

	cpt = 0;
	while (s[i] == BACK_S)
	{
		i++;
		cpt++;
	}
	if (s[i] && s[i] == c && cpt % 2 != 0)
		i++;
	return (i);
}

static int	comptword(char *s, char c)
{
	int		word;
	int		i;

	word = 1;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
			i = for_the_norm(s, i);
		else if (s[i] == BACK_S)
			i = split_back(s, i, c);
		else if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != '\0')
				word++;
		}
		else if (s[i] != '\0')
			i++;
	}
	return (word);
}

static int	comptcaractere(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
			i = for_the_norm(s, i);
		else if (s[i] == BACK_S && c != ' ')
			i = split_back(s, i, c);
		else if (s[i] != '\0')
			i++;
	}
	return (i);
}

char		**ft_split_space(char *s, char c)
{
	char	**resultat;
	int		caractere;
	int		word;
	int		i;

	i = 0;
	if (!s)
		return (0);
	word = comptword((char*)s, c);
	resultat = (char**)malloc(sizeof(char*) * (word + 1));
	if (!resultat)
		return (0);
	while (i < word)
	{
		caractere = 0;
		while (*s && *s == c)
			s++;
		caractere = comptcaractere((char*)s, c);
		resultat[i] = ft_substr(s, 0, caractere);
		while (caractere-- > 0)
			s++;
		i++;
	}
	resultat[i] = NULL;
	return (resultat);
}
