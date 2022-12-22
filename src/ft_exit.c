/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:25:31 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:25:33 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_atoi_error(int *atoi_error)
{
	*atoi_error = -1;
	return (-1);
}

long long	static	ft_special_atoi(const char *str, int *atoi_error)
{
	int			i;
	int			valorfinal;
	long long	nbr;

	nbr = 0;
	i = 0;
	valorfinal = 1;
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
			return (ft_atoi_error(atoi_error));
		if (nbr > LLONG_MAX && valorfinal == 1)
			return (ft_atoi_error(atoi_error));
	}
	return (nbr * valorfinal);
}

void	return_value_exit(long long n)
{
	while (n > 255)
		n = n - 256;
	while (n < -255)
		n = n + 256;
	if (n < 0)
		n = n + 256;
	printf("exit\n");
	exit (n);
}

int	check_only_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9'))
		{
			put_error("exit\nbash: exit", s, "numeric argument required");
			exit (255);
		}
		i++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	long long	n;
	int			atoi_error;
	int			i;

	if (cmd->arg[0])
		cmd->arg[0] = str_noquotes(cmd->arg[0]);
	atoi_error = 0;
	if (cmd->num_arg == 0 || !cmd->arg[0])
		exit (g_error);
	else if (cmd->arg[1] && check_only_num(cmd->arg[0]))
		return (put_error("exit\nbash", "exit", "too many arguments"));
	i = -1;
	while (cmd->arg[++i])
		check_only_num(cmd->arg[i]);
	n = ft_special_atoi(cmd->arg[0], &atoi_error);
	if (atoi_error == -1)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", cmd->arg[0]);
		exit (255);
	}
	return_value_exit (n);
}
