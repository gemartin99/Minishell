#include "minishell.h"

char *get_path()
{
	char *s;
	char *res;
	int i;

	i = 0;
	s = malloc(sizeof(char) * (MAXPATHLEN + 1));
	getcwd(s, MAXPATHLEN);
	while (s[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		ft_free();
	i = -1;
	while (s[++i])
		res[i] = s[i];
	free(s);
	res[++i] = '\0';
	return (res);
}

/*
char *quit_url_extension(char *path, char *res)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	while (path[--i])
	{
		if (path[i] == '/')
		{
			//path[i] = '/';
			path[i] = '\0';
			break ;
		}
	}
	i = 0;
	res = malloc(sizeof(char) * i + 1);
	i = -1;
	while (path[++i])
		res[i] = path[i];
	res[i] = '\0';
	free(path);
	return (res);
}
*/

int ft_cd(t_list *d)
{
	char *path;
	int i;

	path = get_path();
	i = 0;
	if (d->num_args == 1)
		chdir(getenv("HOME"));
	if (d->num_args == 2)
		chdir(d->argu[1]);
	return (0);
}