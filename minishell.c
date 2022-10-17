/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*void ft_free_d(t_list *d)
{
	int i;

	i = 0;
	while (i < d->num_args)
	{
		free(d->argu[i]);
		i++;
	}
	if (d->argu)
		free(d->argu);
	if (d->read_line)
		free(d->read_line);
	if (d->result)
		free(d->result);
}*/

static int var_strcmp_path(char *s1, char *s2) //funcion strcmp modificada para variables de entorno path
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s2[i] && s2[i] != '=')
		i++;
	if (ft_strlen(s1) != i)
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

int path_exist(t_list *d) //funcion que checkea si existe la var $PATH
{
	int i;

	i = -1;
	while (++i < d->num_env)
	{
		if (d->ent_var[i] == NULL)
			;
		else if (var_strcmp_path("PATH", d->ent_var[i]) == 0)
		{
			d->path_value = ft_strdup(d->ent_var[i]);
			i = 0;
			while (*d->path_value != '=')
				d->path_value++;
			d->path_value++;
			return (0);
		}
	}
	return (-1);
}

char *value_dolar_path(char *s)
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
		ft_free();
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

char *increase_pointer(char *s)
{
	int i;
	int j;
	char *res;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s);
	while (s[i] && s[i] != ':')
		i++;
	res = malloc(sizeof(char) * j - i + 1);
	if (!res)
		ft_free();
	j = 0;
	while (s[++i])
	{
		res[j] = s[i];
		j++;
	}
	res[j] = '\0';
	return (res);
}

//funcion para ejecutar 
int ft_try_to_exec(t_list *d) //funcion para intentar hacer execv de lo que me manden
{
	int returnvalue;
	char *absolute_path;
	char *search_path;
	pid_t pid;
//	const char *test;

//	test = malloc(sizeof(char) * ft_strlen(d->argu[0]) + 1);
	int i;

//	i = -1;
//	while (d->argu[0][++i])
//		test[i] = d->argu[0][i];
//	test[i] = '\0';
	i = 0;
	if (path_exist(d) == -1)
		printf("$PATH NO EXISTE\n");
	//char cmd[] = "/bin/ls";
	//char * argVec[] = {"ls", "-la", NULL};
	//char * envVec[] = {NULL};
	//printf("c %s\n", absolute_path);
	absolute_path = ft_strdup("a");
	while (absolute_path) //ARREGLAR: NOSE PORQUE ME SALE EL PROMPT CUANDO HAGO FORK
	{
		absolute_path = value_dolar_path(d->path_value);
		d->path_value = increase_pointer(d->path_value);
		//printf("%s\n", absolute_path);
		//printf("%s\n", d->path_value);
		pid = fork();
		if (pid == 0)
		{
			absolute_path = value_dolar_path(d->path_value);
			d->path_value = increase_pointer(d->path_value);
			search_path = ft_strjoin(absolute_path, d->argu[0]);
			//printf("\na %s\n", search_path);
			//printf("|%s|\n", d->argu[0]);
			if (access(search_path, F_OK) != -1)
			{
				returnvalue = execve(search_path, &d->argu[0], d->ent_var);
				printf("%d\n", returnvalue);
				if (returnvalue == 0 || returnvalue == 1)
					exit (0);
				else
					exit (255);
			}
			else
					exit (255);
		}
	}
	return (0);
}

int check_fst_arg(t_list *d) //funcion para filtrar los builtings o para execv
{
	if (check_echo_word(d->argu[0]) == 0)
		return (ft_echo(d));
	else if (check_pwd_word(d->argu[0]) == 0)
		return (ft_pwd(0));
	else if (ft_strcmp(d->argu[0], "cd") == 0)
		return (ft_cd(d));
	else if (check_env_word(d->argu[0]) == 0)
		return (ft_env(d));
	else if (ft_strcmp(d->argu[0], "export") == 0)
		return (ft_export(d));
	else if (ft_strcmp(d->argu[0], "unset") == 0)
		return (ft_unset(d));
	else if (ft_strcmp(d->argu[0], "exit") == 0)
	{
		ft_exit(d);
		return (0);
	}
	else
	{
		printf("NO BUILTIN\n\n\n");
		ft_try_to_exec(d);
	}
	return (0);
}

/*void init_prompt(t_list *d)
{
}
*/
//funcion para checkear el numero de tokens que hay

void	many_args(char **argv) //funcion para si cuando vas a correr el programa por primera vez y introduces ciertos args se muestre esto
{
	if (ft_strcmp(argv[0], argv[1]) == 0)
		{
			printf("%s: %s: cannot execute binary file\n", argv[0], argv[1]);
			exit(0);
		}
		printf("%s: %s: No such file or directory\n", argv[0], argv[1]);
		exit(0);
}

int init_env(t_list *d, char **envp) //funcion para inicializar el valor de las variables de entorno
{
	int i;

	i = 0;
	d->atoi_error = 0;
	d->echo_control = 0;
	while (envp[i])
		i++;
	d->num_env = i;
	d->ent_var = malloc(sizeof(char *) * (d->num_env));
	if (d->ent_var == NULL)
		return (-1);
	i = 0;
	while (i < d->num_env)
	{
		d->ent_var[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		i++;
	}
	return (0);
}

int ft_launch_minishell(int argc, char **argv, char **envp) //funcion para los testers
{
	t_list d;

	if (argc <= 2)
		return(0);
	if (init_env(&d, envp) == -1)
		return (-1); //ft_free()
		d.quotes = 0;
		//init_prompt(&d);
		// d.read_line = readline("Minishell 🥵🇪🇸 ->");
		// if (d.read_line[0] == '\0')
		// 	printf("");
		// else
		//{
			d.read_line = argv[2];
			//add_history(d.read_line);
			if (d.read_line && parsing(d.read_line, &d) == -1)
				return (printf("ERROR EN EL PARSING\n"));
			//add_history(d.read_line);
			if (check_null_args(d.read_line, &d, 0) == -1)
				parsing(d.read_line, &d);
			if (d.read_line && d.quotes == 0 && check_fst_arg(&d) == -1)
				return (printf("ERROR DE RETORNO \n"));
		//ft_free_d(&d);
		//}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_list d;
	//int		exit_status;

	/*if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		exit_status = ft_test(argc, argv, envp, &d);
		exit(exit_status);
	}*/
	//este if es para los testers
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
  	{
    	int exit_status = ft_launch_minishell(argc, argv, envp);
    	exit(exit_status);
    }
	if (argc != 1)
		many_args(argv);
	if (init_env(&d, envp) == -1)
		return (-1); //ft_free()
	while (1)
	{
		d.quotes = 0;
		//init_prompt(&d);
		d.read_line = readline("Minishell 🥵🇪🇸 ->");
		if (d.read_line[0] == '\0')
			printf("");
		else
		{
			add_history(d.read_line);
			if (d.read_line && parsing(d.read_line, &d) == -1)
				return (printf("ERROR EN EL PARSING\n"));
			//add_history(d.read_line);
			if (check_null_args(d.read_line, &d, 0) == -1)
				parsing(d.read_line, &d);
			if (d.read_line && d.quotes == 0 && check_fst_arg(&d) == -1)
				return (printf("ERROR DE RETORNO \n"));
		//ft_free_d(&d);
		}
	}
	return (0);
}

//funcion para el tester
/*int	ft_test(int argc, char **argv, char **envp, t_list *d)
{
	char		*input;

	(void)argc;
	(void)envp;
	d->quotes = 0;
	//if (set_signal())
	//	return (1);
	input = ft_strdup(argv[2]);
	d->result = ft_strdup(input);
	parsing(d->result, d);
	check_fst_arg(d);
	//if (!lexer(&shell, 0, 0))
	//	parser(&shell);
	return (0);
}*/

