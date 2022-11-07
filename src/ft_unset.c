/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

static int ft_check_wrong_let(char c, char *s)
{
	if (c == '=' || c == '?' || c == '!' || c == '.'
		|| c == '+' || c == '}' || c == '{' || c == '-' || c == 92
		|| c == '[' || c == ']' || c == '@' || c == '*' || c == '#'
		|| c == '^')
	{
		printf("bash: unset: `%s': not a valid identifier\n", s);
		return (-1);
	}
	return (0);
}

int	ft_special_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s2)
		return (-1);
	while (s2[i] && s2[i + 1] && s2[i + 1] != '=' && s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	ft_unset_strcmp(char *s, t_msh *d)
{
	int	i;

	i = -1;
	if (!s[0] || s[0] == '=' || s[0] == '?' || s[0] == '!')
	{
		printf("bash: unset: `%s': not a valid identifier\n", s);
		return (0);
	}
	while (s[++i])
	{
		if (ft_check_wrong_let(s[i], s) == -1)
			return (0);
	}
	while (++i < d->num_env)
	{
		if (ft_special_strcmp(s, d->ent_var[i]) == 0)
		{
			d->ent_var[i] = NULL;
			d->num_env--;
			break ;
		}
	}
	return (0);
}

int	ft_unset(t_msh *d)
{
	int	i;

	i = 1;
	while (i < d->num_args)
	{
		if (ft_unset_strcmp(d->argu[i], d) == 0)
			;
		i++;
	}
	return (0);
}