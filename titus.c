#include <stdio.h>

int main ()
{
	char str[10] = {0};

printf("\n\nComment tu t'appel ?");
fgets(str, 10, stdin);
printf ("\nBonjour %s !!\n", str);

return(0);
}
