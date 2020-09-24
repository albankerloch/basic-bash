#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include "./libft/libft.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char *line;
	int	r;
/*	char *buf;

	buf = malloc(5000);
	//printf("lol test %s\n", av[1]);
	//printf("pt=%s\n", pt);
	char *pat = "/home/user42/Documents/cub3d";
	chdir(pat);
	//chdir("..");
	printf("current dir=%s\n", getcwd(buf, PATH_MAX));
	free(buf);*/
	int fd;
	fd = open("texte", O_RDONLY);
	while ((r = get_next_line(fd, &line)) == 1)
	{
		printf("%d %s\n", r, line);
		free (line);
	}
	printf("%d %s\n", r, line);
	free (line);
	close(fd);
	return (0);
}
