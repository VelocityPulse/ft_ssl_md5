
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char command[100100] = {0};
	char a[100000] = {0};
	int i = 0;

	while (1)
	{
		a[i] = i;
		sprintf(command, "echo %s > a%d", a, i);
		i++;

		system(command);
	}
}
