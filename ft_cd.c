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