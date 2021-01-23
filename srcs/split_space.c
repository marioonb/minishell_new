#include "../include/minishell.h"

static int	comptword(char *s, char c)
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
		return (0);
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
	return (resultat);
}

//int main()
//{
//	char *str = "salut \"va bien\" pas";
//	ft_split(str, ' ');
//  	return 0;
//}
