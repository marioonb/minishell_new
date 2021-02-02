#include "../include/minishell.h"

/*static int	comptword(char *s, char c)
{
	int			word;
	int			i;

	word = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == '\\')
			s++;
		else if (*s == c)
			i = 0;
		else if (i == 0)
		{
			i = 1;
			word++;
		}
		s++;
	}
	return (word);
}

static int	comptcaractere(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] == c)
			i++;
		i++;
	}
	return (i);
}

char	**ft_split_minishell(char const *s, char c)
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
		while (*s && *s != c)
			s++;
		i++;
	}
	resultat[i] = NULL;
	return (resultat);
}*/

static int	comptword(char *s, char c)
{
	int			word;
	int			i;

	word = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == '\\')
			s++;
		else if (*s == c)
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
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] == c)
			i++;
		i++;
	}
	return (i);
}

char	**ft_split_minishell(char const *s, char c)
{
	char	**resultat;
	int		caractere;
	int		word;
	int		i;

	resultat = NULL; // a retirer si trop de ligne
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
		if (*s == '\\')
			s++;
		while (*s && *s != c)
			s++;
		i++;
	}
	resultat[i] = NULL;
	return (resultat);
}
