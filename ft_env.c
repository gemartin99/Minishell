#include "minishell.h"

int ft_env(t_list *d)
{
	int i;

	i = 0;
	//1printf("%d\n", d->num_env);
	while (i < d->num_env)
	{
		if (d->ent_var[i] != NULL)
			printf("%s\n", d->ent_var[i]);
		i++;
	}
	return (0);
}