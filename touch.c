#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#include "fcntl.h"

void touch(char * to_be_touched)
{
	int fw;
	fw = open(argv[1], O_CREATE | O_RDWR);
	if (fw<0 )
	{
		printf(1,"error -.-\n");
		exit();
	}
	close(fw);
}

int main (int argc, char* argv[])
{
	int i;
	if (argc>1)
	{
		for (i=1; i<argc;i++)
			touch(argv[i]);
	}
	
	exit();
}