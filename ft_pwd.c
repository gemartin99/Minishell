#include "minishell.h"

int ft_pwd()
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
	res[i] = '\n';
	if (write(1, &res[0], i + 1) != i + 1)
		return (-1);
	return (0);
}