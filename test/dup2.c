#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main()
{
	int	fd1 = open("test", O_CREAT, O_APPEND); // 파일의 끝에 write
} 