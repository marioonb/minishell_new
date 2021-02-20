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

/*static int	comptword(char *s, char c, char p)
{
	int		word;
	int		i;
	char	d;

	word = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == '\'' || *s == '"')
		{
			d = *s;
			s++;
			while (*s && *s != d)
				s++;
		}
		if (*s == c || *s == p)
			i = 0;
		else if (i == 0)
		{
			i = 1;
			word++;
		}
		if (*s != '\0')
			s++;
	}
	return (word);
}

static int	comptcaractere(char *s, char c, char p)
{
	int		i;
	char	d;

	i = 0;
	while ((s[i] != c && s[i] != p) && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			d = s[i];
			i++;
			while (s[i] && s[i] != d)
				i++;
			if (s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (i);
}

char	**ft_split_space(char const *s, char c, char p)
{
	char	**resultat;
	int		caractere;
	int		word;
	int		i;
	char	d;

	i = 0;
	if (!s)
		return (0);
	word = comptword((char*)s, c, p);
	resultat = (char**)malloc(sizeof(char*) * (word + 1));
	if (!resultat)
		return (0);
	while (i < word)
	{
		caractere = 0;
		while (*s && (*s == c || *s == p))
			s++;
		caractere = comptcaractere((char*)s, c, p);
		resultat[i] = ft_substr(s, 0, caractere);
		while (*s && (*s != c && *s != p))
		{
			if (*s == '\'' || *s == '"')
			{
				d = *s;
				s++;
				while (*s && *s != d)
					s++;
				if (*s != '\0')
					s++;
			}
			else
				s++;
		}
		i++;
	}
	resultat[i] = NULL;
	return (resultat);
}
*/
//int main()
//{
//	char *str = "salut \"va bien\" pas";
//	ft_split(str, ' ');
//  	return 0;
//}

/*static int	comptword(char *s, char c)
{
	int		word;
	int		i;
	char	d;

	word = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == '\'' || *s == '"')
		{
			d = *s;
			s++;
			while (*s && *s != d)
				s++;
		}
		if (*s == c)
			i = 0;
		else if (i == 0)
		{
			i = 1;
			word++;
		}
		if (*s != '\0')
			s++;
	}
	return (word);
}

static int	comptcaractere(char *s, char c)
{
	int		i;
	char	d;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			d = s[i];
			i++;
			while (s[i] && s[i] != d)
				i++;
			if (s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (i);
}

char	**ft_split_space(char const *s, char c)
{
	char	**resultat;
	int		caractere;
	int		word;
	int		i;
	char	d;

	i = 0;
	if (!s)
		return (0);
	word = comptword((char*)s, c);
	resultat = (char**)malloc(sizeof(char*) * (word + 1));
	if (!resultat)
		ft_error_malloc();
	while (i < word)
	{
		caractere = 0;
		while (*s && *s == c)
			s++;
		caractere = comptcaractere((char*)s, c);
		resultat[i] = ft_substr(s, 0, caractere);
		while (*s && *s != c)
		{
			if (*s == '\'' || *s == '"')
			{
				d = *s;
				s++;
				while (*s && *s != d)
					s++;
				if (*s != '\0')
					s++;
			}
			else
				s++;
		}
		i++;
	}
	resultat[i] = NULL;
	ft_read_tab_char(resultat);
	return (resultat);
}*/

/*static char	*for_the_norm(char *s)
{
	char	d;

	d = *s;
	s++;
	while (*s && *s != d)
	{
		if (*s == '\\')
			s++;
		s++;
	}
	return (s);
}

static int	comptword(char *s, char c)
{
	int		word;
	int		i;

	word = 0;
	i = 0;
	while (*s != '\0')
	{
		if (*s == '\'' || *s == '"' )
			s = for_the_norm(s);
		if (*s == c)
			i = 0;
		else if (i == 0)
		{
			i = 1;
			word++;
		}
		if (*s != '\0')
			s++;
	}
	return (word);
}

static int	comptcaractere(char *s, char c)
{
	int		i;
	char	d;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			d = s[i];
			i++;
			while (s[i] && s[i] != d)
				i++;
			if (s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (i);
}

char	**ft_split_space(char const *s, char c)
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
		ft_error_malloc();
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
*/

static int	for_the_norm(char *s, int i)
{
	char	d;

	d = s[i];
	i++;
	while (s[i] && s[i] != d)
	{
		if (s[i] == '\\')
			i++;
		i++;
	}
	return (i);
}

static int	comptword(char *s, char c)
{
	int	word;
	int	i;

	word = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"' )
		{
			if (i > 0 && s[i - 1] == '\\') // AJOUTE
				i++; // AJOUTE
			else // AJOUTE
				i = for_the_norm(s, i);
		}
		else if (s[i] == c)
		{
			word++;
			while (s[i] == c)
				i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (word);
}

static int	comptcaractere(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (i > 0 && s[i - 1] == '\\') // ca pas mis dans compt word, a voir
				i++; // a remettre si cas trouvé et a ajoute a compt word
			else
			{
				i = for_the_norm(s, i);
				i++;
			}
		}
		else if (s[i] != '\0')
			i++;
	}
	return (i);
}

char	**ft_split_space(char const *s, char c)
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
