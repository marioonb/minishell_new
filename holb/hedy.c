#include <stdio.h>

void	times_table(void)
{
	int i;
	int j;
	int calc;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			calc = i * j;
			if (j > 0)
			{
				putchar(' ');
				if (calc < 10)
					putchar(' ');
			}
			if (calc < 10)
				putchar(calc + '0');
			else
			{
				putchar(calc / 10 + '0');
				putchar(calc % 10 + '0');
			}
			if (j < 9)
				putchar(',');
			j++;
		}
		putchar('\n');
		i++; // ici j ai enlevé ton n++ du coup et ca a retirer une variqble et une initialisation aussi
	}
}

int main(void)
{
	times_table();
	return (0);
}
