/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:12:31 by mbelorge          #+#    #+#             */
/*   Updated: 2021/02/05 18:58:33 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** 1	standard pour les erreurs générales	---- erreurs diverses, comme une << division par zéro >>
** 2	mauvaise utilisation de commandes intégrées ----- Rarement vue, généralement utilisation du code de sortie 1
** 126	la commande appelée ne peut s'exécuter ----- problème de droits ou commande non exécutable
** 127	<< commande introuvable >> ------ problème possible avec $PATH ou erreur de frappe
** 128	argument invalide pour exit	exit ----- exit prend seulement des arguments de type entier compris entre 0 et 255
** 128+n	signal << n >> d'erreur fatale	kill -9 $PPID d'un script	$? renvoie 137 (128 + 9)
** 130	script terminé avec Control-C --- Control-C est le signal 2 d'erreur fatale, (130 = 128 + 2, voir ci-dessus)
** 255*	code de sortie en dehors de la limite
*/

static int	ft_str_isdigit(char *str)
{
	int	i;
	int	nb;
	int	space;

	i = 0;
	nb = 0;
	space = 0;
	if (*str == '-' || str[0] == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

void	builtin_exit(char **tab)
{
	int	nexit;

	nexit = 0;
	if (!tab[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (tab[1] && (!ft_str_isdigit(tab[1])))
		ft_error_exit(1, tab[1], 2);
	else
		nexit = ft_atoi(tab[1]) % 256;
	if (tab[1] && tab[2])
		ft_error_exit(2, NULL, 1);
	ft_putstr_fd("exit\n", 1);
	exit(nexit);
}
