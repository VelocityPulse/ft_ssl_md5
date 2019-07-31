#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char command[100100] = {0};
	char a[100000] = {0};
	int i = 2000;

	while (1)
	{
		a[i] = 'q';
		sprintf(command, "echo %s > a%d", a, i + 1);
		i++;

		usleep(5000);
		system(command);
	}
}
