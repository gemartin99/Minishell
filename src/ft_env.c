#include "../inc/minishell.h"

int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_env)
	{
		if (env->env[i] != NULL)
			printf("%s\n", env->env[i]);
		i++;
	}
	return (0);
}