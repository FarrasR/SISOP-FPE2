#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#include "fcntl.h"

int main (int argc, char* argv[])
{
	int fw;
	fw = open(argv[1], O_CREATE | O_RDWR);
	if (fw<0 || argc>2)
	{
		printf(1,"error -.-\n");
		exit();
	}
	close(fw);
	exit();
}