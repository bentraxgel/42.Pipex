#include "pipex.h"

int	main()
{
	if (access("/usr/bin/yes", X_OK) == 0)
		printf("true\n");
	else
		printf("false");
}