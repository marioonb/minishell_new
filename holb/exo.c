#include <stdio.h>

int main ()
{
	int i;
	int nb;
	int res;

	i = 0;
	while (i < 10)
	{
		nb = 9;
		res = i;
		putchar('0');
		putchar (',');
		while (nb > 0)
		{
			if (res < 10)
				putchar(' ');
			putchar (' ');
			if (res < 10)
				putchar(res + 48);
			else
				printf("%d", res);
			if (nb > 1)
				putchar (',');
			res = res + i;
			nb--;
		}
		putchar ('\n');
		i++;
	}
}
