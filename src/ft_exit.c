/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

int static atoi_error(t_msh *d)
{
	d->atoi_error = -1;
	return (-1);
}

int	static	ft_spaces(char c)
{
	return (
			c == ' ' || c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r'
	);
}

long long	static ft_special_atoi(const char *str, t_msh *d)
{
	int				i;
	int				valorfinal;
	long long	nbr;

	nbr = 0;
	i = 0;
	valorfinal = 1;
	while (str[i] && ft_spaces(str[i]))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			valorfinal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		if (nbr < -LLONG_MIN && valorfinal == -1)
			return (atoi_error(d));
		if (nbr > LLONG_MAX && valorfinal == 1)
			return (atoi_error(d));
	}
	return (nbr * valorfinal);
}


int ft_validate_num(char c)
{
	if ((c < '0' || c > '9') && c != 34 && c != 39)
		return (1);
	return (0);
}

void return_value_exit(long long n)
{
	//printf("ll %lld\n", n);
	while (n > 255)
		n = n - 256;
	while (n < -255)
		n = n + 256;
	//printf("ll %lld\n", n);
	if (n < 0)
	{
		//printf("ll %lld\n", n);
		n = n + 256;
		//printf("f %lld\n", n);
	}
	//printf("exit value %d\n", n);
	exit (n);
}

char *check_space_and_nums(char *s, t_msh *d)
{
	int i;
	int final_value;
	char *not_res;
	char *res;
	int j;

	j = 0;
	//printf("s %s\n", s);
	not_res = malloc(sizeof(char) * 100);
	if (!not_res)
		ft_free();
	i = 0;
	final_value = 0;
	while(s[i] && s[i] != ' ')
		i++;
	while (s[i] && s[i] == ' ' && s[i + 1] && ft_isdigit(s[i + 1]) != 1)
		i++;
	while (s[i] && (s[i] == 34 || s[i] == 39))
		i++;
	//printf("%s\n %d\n %c\n", s, i, s[i]);
	if (s[i] && s[i + 1] && s[i] == '-' && s[i + 1] >= '0' && s[i + 1] <= '9') //si no tengo comillas esto me lo salto // ARREGLAR
		final_value = 1;
	else if (s[i] && s[i] == '+' && final_value != 1)
		final_value = 0;
	//printf("S: %s\n%c\n%c\n", s, s[i], s[i + 1]);
	while (s[++i])
	{
		if (s[i] == 34)
		{
			while (s[++i] && s[i] != 34)
			{
				not_res[j] = s[i];
				j++;
			}
		}
		else if (s[i] == 39)
		{
			while (s[++i] && s[i] != 39)
			{
				not_res[j] = s[i];
				j++;
			}
		}
		else if (s[i] && s[i] == ' ')
		{
			printf("exit\nbash: exit: too many arguments\n");
			exit (255);
		}
		else if (s[i] && (s[i] == 34 || s[i] == 39))
			;
		else if (s[i] && ft_validate_num(s[i]) == 0 && s[i] != 34 && s[i] != 39)
		{
			not_res[j] = s[i];
			j++;
		}
		else if (s[i] && ft_validate_num(s[i]) == 1)
		{
			//printf("%c\n", s[i]);
			printf("exit\nbash: exit: %s: numeric argument required\n", d->argu[1]);
			exit (255);
		}
	}
	not_res[j] = '\0';
	//printf("%s\n", not_res);
	//printf("size %d\n", ft_strlen(not_res) + final_value + 1);
	res = malloc(sizeof(char) * ft_strlen(not_res) + final_value + 1);
	if (!res)
		ft_free();
	i = -1;
	//printf("ffv %d\n", final_value);
	if (final_value == 1)
		res[++i] = '-';
	while (not_res[++i - final_value])
		res[i] = not_res[i - final_value];
	res[i] = '\0';
	free(not_res);
	//printf("res %s\n", res);
	return(res);
}

void check_only_num(char *s)
{
	int i;

	i = 0;
	//printf("|%s\n", s);
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9'))
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", s);
			exit (255);
		}
		i++;
	}
}

void	ft_exit(t_msh *d)
{
	long long n;
	char *num_in_string;

	if (d->num_args == 1)
		exit (1);
	num_in_string = check_space_and_nums(d->read_line, d);
	check_only_num(num_in_string);
	//printf("|%s|\n", num_in_string);
	n = ft_special_atoi(num_in_string, d);
	//printf("n: %lld\n", n);
	if (n < -9223372036854775807 || n > 9223372036854775807 || d->atoi_error == -1)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", num_in_string);
		//hacer funcion para liberar todo
		exit (255);
	}
	return_value_exit(n);
}