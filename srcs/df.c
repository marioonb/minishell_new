#include <string.h>
#include <stdio.h>
#include "../include/minishell.h"

void    ft_read_tab_char(char **tab)
{
    int    i;
    int    j;

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

static size_t    ft_length(char const *s, unsigned int star, size_t len)
{
    size_t        i;

    i = 0;
    while (s[star] != '\0' && i < len)
    {
        star++;
        i++;
    }
    return (i);
}

char    *ft_substr(char const *s, unsigned int star, size_t len)
{
    char        *resultat;
    size_t        i;
    size_t        j;

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

static int    for_the_norm(char *s, int i, int a)
{
    char    d;

    d = s[i];
    i++;
    while (s[i] && s[i] != d)
    {
        if (s[i] == '\\')
            i++;
        i++;
    }
    //if (s[i] && s[i] == '"' && a == 1)
          i++;
    return (i);
}

static int    comptword(char *s, char c)
{
    int    word;
    int    i;

    word = 1;
    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\'' || s[i] == '"' )
        {
            if (i > 0 && s[i - 1] == '\\') // AJOUTE
                i++; // AJOUTE
            else // AJOUTE
                i = for_the_norm(s, i, 2);
        }
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

static int    comptcaractere(char *s, char c)
{
    int    i;

    i = 0;
    while (s[i] != c && s[i] != '\0')
    {
        if (s[i] == '\'' || s[i] == '"')
        {
          if (i > 0 && s[i - 1] == '\\') // ca pas mis dans compt word, a voir
                i++; // a remettre si cas trouvé et a ajoute a compt word
            else
            i = for_the_norm(s, i, 2);
        }
        else if (s[i] != '\0')
            i++;
    }
    return (i);
}

char    **ft_split_space(char const *s, char c)
{
    char    **resultat;
    int        caractere;
    int        word;
    int        i;

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


int main() {

//char *t= "echo \'ma\' ; ec \'sd\'";
char *t= "eho \"ma\" ; ec";
char **s = ft_split_space(t, ';');
ft_read_tab_char (s);
  return 0;
}
