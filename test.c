#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

int main(int ac, char **av)
{
	char *buf;

	buf = malloc(5000);
	(void)ac;
	(void)av;
	//printf("lol test %s\n", av[1]);
	//printf("pt=%s\n", pt);
	char *pat = "/home/user42/Documents/cub3d";
	chdir(pat);
	//chdir("..");
	printf("current dir=%s\n", getcwd(buf, PATH_MAX));
	free(buf);
	return (0);
}
