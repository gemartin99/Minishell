/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 02:37:22 by smiro             #+#    #+#             */
/*   Updated: 2022/12/07 02:37:24 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

void	many_args(char **argv) //funcion para si cuando vas a correr el programa por primera vez y introduces ciertos args se muestre esto
{
	size_t	len;

	len = ft_strlen(argv[0]);
	if (ft_strlen(argv[0]) < ft_strlen(argv[1]))
		len = ft_strlen(argv[1]);
	if (ft_strncmp(argv[0], argv[1], len) == 0)
		put_error(argv[0], argv[1], "cannot execute binary file");
	else
		put_error(argv[0], argv[1], "No such file or directory");
	exit(127);
}

void	exit_error(char *str, int n)
{
	printf("%s\n", str);
	exit(n);
}

void	put_error(char *bash, char *file, char *error)
{
	ft_putstr_fd(bash, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (error)
		ft_putendl_fd(error, 2);
}