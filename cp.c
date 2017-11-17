#include <stdio.h>

int main (int argc, char* argv[])
{
	if (argc>3)
	{
		printf("not yet implemented\n");
		return -1;
	}
	FILE * source, *dest;
	dest= fopen(argv[1], "w");
	source= fopen(argv[2], "r");
	char buffer;
	while ((buffer = fgetc(source))!=EOF)
	{
		fprintf(dest, "%c", buffer);
	}
}