#include "../include/minishell.h"

static size_t	ft_length(char const *s, unsigned int star, size_t len)
{
	size_t		i;

	i = 0;
	while (s[star] != '\0' && i < len)
	{
		star++;
		i++;
	}
	return (i);
}

char			*ft_substr(char const *s, unsigned int star, size_t len)
{
	char		*resultat;
	size_t		i;
	size_t		j;

	resultat = NULL;
	i = 0;
	j = 0;
	resultat = malloc(sizeof(char) * (ft_length(s, star, len) + 1));
	if (!resultat)
		return (0);
	while (s[i] != '\0' && len > 0)
	{
		if (i >= star)
		{
			resultat[j] = s[i];
			j++;
			len--;
		}
		i++;
	}
	resultat[j] = '\0';
	return (resultat);
}
static int	comptword(char *s, char c, char d)
{
	int		word;
	int		i;

	word = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == c || *s == d)
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

static int	comptcaractere(char *s, char c, char d)
{
	int i;

	i = 0;
	while ((s[i] != c && s[i] != d) && s[i] != '\0')
		i++;
	return (i);
}

char		**ft_split_double(char const *s, char c, char d)
{
	char	**resultat;
	int		caractere;
	int		word;
	int		i;

	i = 0;
	if (!s)
		return (0);
	word = comptword((char*)s, c, d);
	resultat = (char**)malloc(sizeof(char*) * (word + 1));
	if (!resultat)
		return (0);
	while (i < word)
	{
		caractere = 0;
		while (*s && (*s == c || *s == d))
			s++;
		caractere = comptcaractere((char*)s, c, d);
		resultat[i] = ft_substr(s, 0, caractere);
		while (*s && (*s != c && *s != d))
			s++;
		i++;
	}
	resultat[i] = NULL;
	return (resultat);
}
