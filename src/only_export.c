#include "../inc/minishell.h"

char *search_lowest(char **env2) //funcion para buscar la primera variable de entorno (alfabeticamente)
{
	int i;
	int j;
	char *res;

	i = -1;
	j = 0;
	//while (env2[++i])
	//	printf("LE LLEGA: %s\n", env2[i]);
	i = 0;
	res = env2[0];
	if (!env2[i + 1])
		env2[0] = NULL;
	while (env2[i])
	{
		if (ft_strncmp(env2[j], env2[i], ft_strlen(res)) > 0)
		{
			res = env2[i];
			j = i;
		}
		i++;
	}
	env2[j] = env2[i - 1];
	env2[i - 1] = NULL;
	return (res);
}

char **dup_env(char **env2, t_cmd *cmd) //funcion que duplica las variables de entorno actuales
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < cmd->env->num_env)
	{
		if (cmd->env->env[i + j] == NULL)
			i++;
		else
		{
			env2[j] = cmd->env->env[i + j];
			j++;
		}
	}
	env2[j - i] = NULL;
	return (env2);
}

char **ft_ord_env(char **res, t_cmd *cmd)
{
	int i;
	char **env2;

	env2 = malloc(sizeof(char *) * cmd->env->num_env + 1);
	if (!env2)
		exit_error("Error malloc", 29);
	env2 = dup_env(env2, cmd);
	i = 0;
	while (cmd->env->num_env - i)
		res[i++] = search_lowest(env2);
	return (res);
}

void	print_export_var(t_cmd *cmd)
{
	int i;
	char **res;

	i = 0;
	res = malloc(sizeof(char *) * cmd->env->num_env + 1);
	if (!res)
		exit_error("Error malloc", 28);
	res = ft_ord_env(res, cmd);
	while (i < cmd->env->num_env)
	{
		if (res[i] != NULL)
			printf("declare -x %s\n", res[i]);
		i++;
	}
}