#include "pipex.h"

int	main()
{
	if (access("cat", X_OK) == 0)
		printf("true\n");
	else
		printf("false");
}