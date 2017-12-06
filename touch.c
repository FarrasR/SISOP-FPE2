#include <syscall.h>
#include <stdio.h>

#include <xv6/stdio.h>
#include <xv6/fcntl.h>
// #include <xv6/fs.h>

void touch(char * to_be_touched)
{
	int fw;
	fw = open(to_be_touched, O_CREAT | O_RDWR);
	if (fw<0)
	{
		printf("touch: can't create file: %s\n", to_be_touched);
		// exit();
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
	sysexit();
	// exit()
;}