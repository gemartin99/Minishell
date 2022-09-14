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

void	ft_free()
{
	printf("FALLA RESERVA MEMORIA\n");
	exit (0);
}

int ft_try_to_exec(t_list *d)
{
	if (d->num_args == 1)
	{
		if (execve ("/usr/bin/ls", d->argu, d->ent_var) == -1)
			//printf("%s\n", d->argu[1]);
			perror("execv failed");
	}
	return (0);
}

int check_fst_arg(t_list *d)
{
	if (check_echo_word(d->argu[0]) == 0)
		return (ft_echo(d));
	else if (ft_strcmp(d->argu[0], "pwd") == 0)
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
		ft_try_to_exec(d);
	}
	return (0);
}

/////////////////////////////////////---Parse ⬇️---/////////////////////////////////////////////////

int count_args(char *s)
{
	int i;
	int res;

	i = -1;
	res = 0;
	if (!s)
		return (res);
	while (s[++i])
	{
		if ((s[i] != 32 && s[i] != 34 && s[i] != 39) && (s[i + 1] == 32 || s[i + 1] == '\0'
			|| s[i + 1] == 34 || s[i + 1] == 39))
			res++;
		if (s[i] == 34)
		{
			res++;
			while (s[++i] != 34)
				;
		}
		if (s[i] == 39)
		{
			res++;
			while (s[++i] != 39)
				;
			i++; 
		}
	}
	return (res);
}

void ft_free_arg(t_list *d)  //funcion por si falla una reserva de memoria de substr
{
	int i;

	i = -1;
	while (d->argu[++i])
		free(d->argu[i]);
	free(d->argu);
}

int choose_arg(char *s, t_list *d)
{
	int pos;
	int i;
	int start;

	d->num_args = count_args(s);
	d->argu = malloc(sizeof(char *) * (d->num_args));
	if (d->argu == NULL)
		return (-1);
	i = -1;
	start = 0;
	pos = 0;
	while (s[++i])
	{
		if (s[i] == 34)
		{
			start = i + 1;
			while (s[++i] != 34)
				;
			d->argu[pos] = ft_substr(s, start, i - start);
			if (d->argu[pos] == NULL)
			{
				ft_free_arg(d);
				return (-1);
			}
			pos++;
		}
		if (s[i] == 39)
		{
			start = i + 1;
			while (s[++i] != 39)
				;
			d->argu[pos] = ft_substr(s, start, i - start);
			if (d->argu[pos] == NULL)
			{
				ft_free_arg(d);
				return (-1);
			}
			pos++;
		}
		if ((s[i] == ' ' || s[i] == 34 || s[i] == 39) && s[i + 1] != ' ')
			start = i + 1;
		if ((s[i] != ' ' && s[i] != 34 && s[i] != 39) && (s[i + 1] == ' ' || s[i + 1] == '\0'
			|| s[i + 1] == 34 || s[i + 1] == 39))
		{
			d->argu[pos] = ft_substr(s, start, i - start + 1);
			if (d->argu[pos] == NULL)
			{
				ft_free_arg(d);
				return (-1);
			}
			pos++;
		}
	}
	return (0);
}

int parsing(char *s, t_list *d)
{
	int i;
	int simple = 0;
	int doble = 0;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34)
		{
			doble++;
			while (s[i + 1] && s[i + 1] != 34)
				i++;
			if (s[i + 1] == 34)
				doble++;
			i++;
		}
		if (s[i] == 39)
		{
			simple++;
			while (s[i + 1] && s[i + 1] != 39)
				i++;
			if (s[i + 1] == 39)
				simple++;
			i++;
		}
	}
	if (doble % 2 != 0 || simple % 2 != 0)
	{
		d->quotes = 1;
		printf("dquote>\n");
		return (0);
	}
	if (choose_arg(s, d) == -1)
		return (-1);
	return (0);
}
/////////////////////////////////////---Parse ⬆️---/////////////////////////////////////////////////

/*void init_prompt(t_list *d)
{
}
*/
//funcion para checkear el numero de tokens que hay

void	many_args(char **argv) //
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

//funcion para el tester
int	ft_test(int argc, char **argv, char **envp, t_list *d)
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
}

int main(int argc, char **argv, char **envp)
{
	t_list d;
	int		exit_status;

	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		exit_status = ft_test(argc, argv, envp, &d);
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
		if (!d.read_line)
		{
			printf("aaaaa\n");
			break ;
		}
		if (d.read_line && parsing(d.read_line, &d) == -1)
			return (printf("ERROR EN EL PARSING\n"));
		add_history(d.read_line);
		if (d.read_line && d.quotes == 0 && check_fst_arg(&d) == -1)
			return (printf("ERROR DE RETORNO \n"));
	}
	return (0);
}
