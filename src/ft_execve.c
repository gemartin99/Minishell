//IMPORTANTE cuando esten las redirecciones hechas añadir el mensaje de error: No such file or directory. Ej bash: <to_file_no_exist

#include "../inc/minishell.h"

static int var_strcmp_path(char *s1, char *s2) //funcion strcmp modificada para variables de entorno path
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s2[i] && s2[i] != '=')
		i++;
	if (ft_strlen(s1) != (size_t)i)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}


int path_exist(t_cmd *cmd, char **path_value) //funcion que checkea si existe la var $PATH
{
	int i;
	char *tmp;

	i = -1;
	while (++i < cmd->env->num_env)
	{
		if (cmd->env->env[i] == NULL)
			;
		else if (var_strcmp_path("PATH", cmd->env->env[i]) == 0)
		{
			tmp = ft_strdup(cmd->env->env[i]);
			i = 0;
			while (*tmp && *tmp != '=')
				tmp++;
			tmp++;
			*path_value = tmp;
			//free(tmp);
			return (0);
		}
	}
	return (-1);
}

/*int path_exist(t_cmd *cmd, char **path_value) //funcion que checkea si existe la var $PATH
{
	int i;
	int j;
	char *tmp;

	i = -1;
	j = 0;
	printf("nenv %d\n", cmd->env->num_env);
	printf("aaa%s\n", cmd->env->env[0]);
	printf("%s\n", "hola");
	while (++i < cmd->env->num_env)
	{
		printf("i: %d\n", i);
		if (cmd->env->env[i] == NULL)
			;
		else if (var_strcmp_path("PATH", cmd->env->env[i]) == 0)
		{
			tmp = ft_strdup(cmd->env->env[i]);
			//printf("PATH es: %s\n", *path_value);
			i = 0;
			//printf("ppp %c\n", *path_value[j]);
			while (*path_value[j] && *path_value[j] != '=')
				j++;
			printf("aaa1\n");
			*path_value = ft_substr(*path_value, j + 1, ft_strlen(*path_value) - j);
			printf("aaa2\n");
			printf("s: %s\n", *path_value);
			exit (0);
		}
	}
	return (-1);
}*/

char *value_dolar_path(char *s) //funcion que muestra el valor de la variable path pero se ira acortando cada vez que se intente ejecutar algo en una de las rutas
{
	int i;
	char *res;

	i = 0;
	if (!s || !s[i])
		return (NULL);
	while (s[i] && s[i] != ':')
		i++;
	res = malloc(sizeof(char) * i + 2);
	if (!res)
		exit_error("Error malloc", 25);
	i = 0;
	while (*s && *s != ':')
	{
		res[i] = *s;
		s++;
		i++;
	}
	res[i] = '/';
	res[i + 1] = '\0';
	return (res);
}

char *increase_pointer(char *s) //funcion que incrementa el indice de la variable path hacia todas las rutas
{
	size_t i;
	size_t j;
	char *res;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s);
	while (s[i] && s[i] != ':')
		i++;
	res = malloc(sizeof(char) * j - i + 1);
	if (!res)
		exit_error("Error malloc", 26);
	j = 0;
	while (res && s[++i])
	{
		res[j] = s[i];
		j++;
	}
	res[j] = '\0';
	return (res);
}

int ft_count_env(t_cmd *cmd) //funcion para contar todas las variables de entorno que no sean nulas.
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i + j < cmd->env->num_env)
	{
		if (cmd->env->env[i + j])
			i++;
		else
			j++;
	}
	return (i - j);
}

char **convert_to_env(t_cmd *cmd) //funcion que retorna una variable que guarde todas las variables de entorno actuales.
{
	int i;
	int j;
	char **res;

	i = ft_count_env(cmd);
	res = malloc(sizeof(char *) * i + 1);
	if (!res)
		exit_error("Error malloc", 27);
	i = -1;
	j = 0;
	while (++i < cmd->env->num_env)
	{
		if (cmd->env->env[i])
		{
			res[j] = cmd->env->env[i];
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}


int ft_try_to_exec(t_cmd *cmd) //funcion para intentar hacer execv de lo que me manden
{
	//CHECKEAR SI ME MANDAN PATH ABSOLUTA Y SI LO HACEN EJECUTAR ESO DIRECTAMENTE

	int returnvalue = EXIT_FAILURE;
	char *absolute_path;
	char *search_path;
	char *path_value;
	char **envp_2; //variable creada porque se asignan variables a NULL (en vez de borrar) cuando se hace unset entonces no funcionaria execve correctamente con el ent_var de la estructura
	pid_t pid;
	int status;

	if (path_exist(cmd, &path_value) == -1)
		printf("$PATH NO EXISTE\n");
	/*envp_2 = convert_to_env(cmd);
	absolute_path = ft_strdup("a");
	while (absolute_path)
	{
		absolute_path = value_dolar_path(d->path_value);
		d->path_value = increase_pointer(d->path_value);
		pid = fork();
		if (pid < 0)
			ft_free();
		else if (pid == 0)
		{
			absolute_path = value_dolar_path(d->path_value);
			d->path_value = increase_pointer(d->path_value);
			search_path = ft_strjoin(absolute_path, d->argu[0]);
			if (access(search_path, F_OK) != -1)
			{
				if (access(search_path, X_OK) != -1)
				{
					returnvalue = execve(search_path, d->argu, envp_2); //poner variables de entorno propias para que los comandos que necesiten las env las puedan utilizar
					exit(0);
				}
				printf("bash: %s: Permision denied\n", d->argu[0]);
				exit (1);

			}
			else
				exit(255);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				returnvalue = WEXITSTATUS(status);
			if (returnvalue == 0 || returnvalue == 1)
				break;
		}
	}
	if (returnvalue != 0 && returnvalue != 1)
		printf("bash: %s: Command not found\n", d->argu[0]);*/
	return (0);
}