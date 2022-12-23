/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:24:52 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:24:54 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

static int	ft_check_wrong_let(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=' || s[i] == '?' || s[i] == '!' || s[i] == '.'
			|| s[i] == '+' || s[i] == '}' || s[i] == '{' || s[i] == '-'
			|| s[i] == 92 || s[i] == '[' || s[i] == ']' || s[i] == '@'
			|| s[i] == '*' || s[i] == '#' || s[i] == '^' || s[i] == '~')
		{
			put_error("bash: unset", s, "not a valid identifier");
			return (1);
		}
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

int	ft_unset_strcmp(char *s, t_env *env)
{
	int	i;

	i = -1;
	if (ft_strncmp(s, "PATH", 5) == 0)
	{
		free(env->path);
		env->path = "./";
	}
	if (ft_check_wrong_let(s))
		return (1);
	while (++i < env->num_env)
	{
		if (ft_special_strcmp(s, env->env[i]) == 0)
		{
			free(env->env[i]);
			env->env[i] = NULL;
			env->num_env--;
			break ;
		}
	}
	return (0);
}

int	ft_unset(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd)->num_arg)
	{
		if (ft_unset_strcmp((*cmd)->arg[i], (*cmd)->env))
			return (1);
		i++;
	}
	return (0);
}
