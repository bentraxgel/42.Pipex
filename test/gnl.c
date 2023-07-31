#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	if (len == 0)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while ((*s1 && *s2) && len--)
	{
		if (*s1 != *s2)
			break ;
		else if (len)
		{
			s1++;
			s2++;
		}
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	main(int ac, char *av[])
{
	char *ret;
	int	i = 0;

	char	*limiter = ft_strjoin(av[1], "\n");
	printf("limiter : %s+\n+", limiter);
	for (int i = 0; av[i]; i++)
		printf("av[%d] : %s\n", i, av[i]);
	printf("\nav[1] :  %zu : %s\n", ft_strlen(av[1]), av[1]);
	while (get_next_line(0, &ret) == true)
	{
		printf("[i] : %s+", ret);
		int v = ft_strncmp(ret, limiter, ft_strlen(av[1]) + 1);
		printf("ncmp : %d\n", v);
		if (v == 0){
			printf("compare\n");
			exit(10);
		}
	}
}