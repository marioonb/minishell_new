/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelorge <mbelorge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:32:51 by mbelorge          #+#    #+#             */
/*   Updated: 2020/08/01 22:19:58 by mbelorge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static void	ft_conversiontype(char *str, va_list *arg, int fd)
{
	char	c;
	char	*s;
	int		num;
	char	*n;

	s = NULL;
	if (str[0] == 'c')
	{
		c = va_arg(*arg, int);
		ft_putchar_fd(c, fd);
	}
	else if (str[0] == 's')
	{
		s = va_arg(*arg, char *);
		if (s == NULL)
			s = "(null)";
		ft_putstr_fd(s, fd);
	}
	else if (str[0] == 'd')
	{
		num = va_arg(*arg, int);
		n = ft_itoa(num);
		ft_putstr_fd(n, fd);
		free(n);
	}
}

static void	ft_printfrun(char *str, va_list *arg, int fd)
{
	while (*str)
	{
		if (*str != '%')
			ft_putchar_fd(str[0], fd);
		else
		{
			str++;
			ft_conversiontype(&str[0], arg, fd);
			while (!ft_isalpha(*str) && *str != '%')
				str++;
		}
		str++;
	}
}

int			mini_printf_fd(int fd, const char *s, ...)
{
	char	*str;
	va_list	arg;

	str = (char*)s;
	va_start(arg, s);
	if (fstrchr(s, '%') == NULL)
	{
		ft_putstr_fd(str, fd);
		return (0);
	}
	ft_printfrun(str, &arg, fd);
	va_end(arg);
	return (0);
}
