void caractere (char c)
{

if (c = 33 || (c >=35 && c <= 37) || (c >= 42 && c <= 47) ||
	c == 58 || c == 63 || c = 64 || c == 91 || c == 93 || c == 94 ||
	c == 123 || c == 125 || c == 126 || c == 61)
		printf ("\nles caractere a ecrire, affiche la variable ainsi qu eux meme");
else if (ft_isalnum(c))
		printf("\nn'affiche rien du tout");
else if (c == 40 || c == 41 || c == 60 || c == 62)
		printf("\nerreur attente de quelque chose");
else if (c == 34 || c == 39 || c == 96 || c == 124)
		printf ("\npas d erreur mais attende quelaue chose");
else if (c == 38)
		printf("\ncreait un truc");
}


