#include "../inc/minishell.h"

int	string_compare(char *s1,char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
char **ft_swap_to_last(char **env2, int i, int j)
{
	char *temp;

	temp = env2[i];
	env2[i] = env2[j];
	env2[j] = temp;
	return (env2);
}

char *search_lowest(char **env2, t_cmd *cmd) //funcion para buscar la primera variable de entorno (alfabeticamente)
{
	int i;
	int j;
	char *res;

	i = 0;
	j = 0;
	while (cmd->env->env[i] && cmd->env->env[i + 1])
	{
		if (string_compare(cmd->env->env[i], cmd->env->env[i + 1]) > 0)
		{
			res = cmd->env->env[i + 1];
			j = i;
		}
		i++;
	}
	i = 0;
	while (cmd->env->env[i])
		i++;
	env2[j] = NULL;
	env2 = ft_swap_to_last(env2, i, j);
	printf("R: %s\n", res);
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
	env2[j] = NULL;
	return (env2);
}

char **ft_ord_env(char **res, t_cmd *cmd)
{
	int i;
	char **env2;
	int b;

	i = -1;
	env2 = malloc(sizeof(char *) * cmd->env->num_env + 1);
	if (!env2)
		exit_error("Error malloc", 29);
	env2 = dup_env(env2, cmd);
	env2[i] = NULL;
	while (++i < cmd->env->num_env)
	{
		b = -1;
		printf("\n\n");
		while (env2[++b])
			printf("ENV2: |%s|\n", env2[b]);
		b = -1;
		while (res[++b])
			printf("RES: |%s|\n", env2[b]);
		printf("\n\n");
		res[i] = search_lowest(env2, cmd);
	}
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
			printf("FIN declare -x %s\n", res[i]);
		i++;
	}
}