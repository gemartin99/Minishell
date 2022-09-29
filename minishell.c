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

//funcion para ejecutar 
int ft_try_to_exec(t_list *d) //funcion para intentar hacer execv de lo que me manden
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		char cmd[] = "/bin/ls";
		char * argVec[] = {"ls", "-la", NULL};
		char * envVec[] = {NULL};

		if (d->num_args == 1)
		{
			if (execve (cmd, argVec, envVec) == -1)
				perror("execv failed");
		}
	}
	else
		;
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
	//else if (ft_strcmp(d->argu[0], "exit") == 0)
	//	ft_free(d);
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

int main(int argc, char **argv, char **envp)
{
	t_list d;
	//int		exit_status;

	/*if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		exit_status = ft_test(argc, argv, envp, &d);
		exit(exit_status);
	}*/
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

