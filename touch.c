#include <stdio.h>

int main (int argc, char* argv[])
{
	FILE * fw;
	fw = fopen(argv[1], "w");
	if (fw==NULL || argc>2)
	{
		printf("error -.-\n");
		return -1;
	}
	fclose(fw);
	return 0;
}