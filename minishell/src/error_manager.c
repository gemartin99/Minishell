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
		printf("%s: %s: cannot execute binary file\n", argv[0], argv[1]);
	else
		printf("%s: %s: No such file or directory\n", argv[0], argv[1]);
	exit(7);
}

void	exit_error(char *str, int n)
{
	printf("%s\n", str);
	exit(n);
}


