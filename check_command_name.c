/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:09:39 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 16:09:44 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int check_echo_word(char *s)
{
	if (s[0] != 'E' && s[0] != 'e')
		return (-1);
	if (s[1] != 'C' && s[1] != 'c')
		return (-1);
	if (s[2] != 'H' && s[2] != 'h')
		return (-1);
	if (s[3] != 'O' && s[3] != 'o')
		return (-1);
	if (s[4])
		return (-1);
	return (0);
}

int	check_env_word(char *s)
{
	if (s[0] != 'E' && s[0] != 'e')
		return (-1);
	if (s[1] != 'N' && s[1] != 'n')
		return (-1);
	if (s[2] != 'V' && s[2] != 'v')
		return (-1);
	if (s[3])
		return (-1);
	return (0);
}

int check_pwd_word(char *s)
{
	if (s[0] != 'P' && s[0] != 'p')
		return (-1);
	if (s[1] != 'W' && s[1] != 'w')
		return (-1);
	if (s[2] != 'D' && s[2] != 'd')
		return (-1);
	if (s[3])
		return (-1);
	return (0);
}