/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_null_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:20:50 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 02:20:53 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char *quit_null(char *s, int i) //funcion para quitar argumentos nulos sin espacios antes y despues
{
	 int j;
	 char *res;

	 printf("1 %c\n2 %c\n", s[i], s[i + 1]);
	 s[i] = 48;
	 s[i + 1] = 48;
	 j = -1;
	 printf("1\n");
	 res = malloc(sizeof(char) * ft_strlen(s)) - 1;
	 if (!res)
	 	exit_error("Error malloc", 10);
	 printf("2\n");
	 while (++j < i)
	 	res[j] = s[j];
	 res[j] = '\0';
	 printf("3\n");
	 printf("%s\n", res);
	 while (s[j + 2])
	 {
	 	res[j] = s[j + 2];
	 	j++;
	 }
	 printf("4\n");
	 res[j] = '\0';
	 if (s)
	 	s = NULL;
	 printf("%s\n", res);
	 return (res);
}

static char *quit_null_space(char *s, int i) //funcion para quitar argumentos nulos si hay espacios antes y despues del argumento
{
	 int j;
	 char *res;

	 s[i] = 48;
	 s[i + 1] = ';';
	 j = -1;
	 res = malloc(sizeof(char) * ft_strlen(s));
	 if (!res)
	 	exit_error("Error malloc", 10);
	 while (++j < i)
	 	res[j] = s[j];
	 while (s[j + 1])
	 {
	 	res[j] = s[j + 1];
	 	j++;
	 }
	 res[j] = '\0';
	 if (s)
	 	s = NULL;
	 return (res);
}


char *change_null_args(char *s, t_cmd *cmd)
{
	int i;

	i = -1;
	while (s[++i])
	{
		printf("IB\n");
		if (s[i] == 34 && s[i + 1] && s[i + 1] != 34)
		{
			printf("1\n");
			while (s[++i] && s[i] != 34)
				;
		}
		else if (s[i] == 39 && s[i + 1] && s[i + 1] != 39)
		{
			printf("2\n");
			while (s[++i] && s[i] != 39)
				;
		}
		else if (s[i] == ' ' && s[i + 1] && (s[i + 1] == 34 || s[i + 1] == 39) && s[i + 2] && (s[i + 2] == 34 || s[i + 2] == 39) && s[i + 3] && s[i + 3] == ' ')
		{
			printf("3\n");
			i++;
			s = quit_null_space(s, i);
			cmd->num_arg--;
			s = change_null_args(s, cmd);
		}
		else if ((s[i] == 34 && s[i + 1] && s[i + 1] == 34) || (s[i] == 39 && s[i + 1] == 39))
		{
			printf("i es igual |%c|\ni + 1 |%c|\ni - 1 |%c|\n", s[i], s[i + 1], s[i -1]);
			printf("4\n");
			s = quit_null(s, i);
			printf("5\n");
			cmd->num_arg--;
			s = change_null_args(s, cmd);
			printf("6\n");
		}
		printf("FB\n");
	}
	return (s);
}

int check_null_args(char *s, int control) //funcion que comprueba si hay null args
{
	int i;
	char *res;

	i = -1;
	while (s[++i])
	{
		if (s[i] == ' ' && s[i + 1] == 34 && s[i + 2] == 34 && s[i + 3] == ' ')
			control = 1;
		else if (s[i] == ' ' && s[i + 1] == 39 && s[i + 2] == 39 && s[i + 3] == ' ')
			control = 1;
		else if ((s[i] == 34 && s[i + 1] == 34) || (s[i] == 39 && s[i + 1] == 39))
			control = 1;
	}
	if (control == 1)
		return (-1);
	return (0);
}
