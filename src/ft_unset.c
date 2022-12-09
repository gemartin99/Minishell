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

void	ft_unset_strcmp(char *s, t_env *env)
{
	int	i;

	i = -1;
	if (!s[0] || s[0] == '=' || s[0] == '?' || s[0] == '!')
	{
		printf("bash: unset: `%s': not a valid identifier\n", s);
		return ;
	}
	while (s[++i])
	{
		if (ft_check_wrong_let(s[i], s) == -1)
			return ;
	}
	while (++i < env->num_env)
	{
		if (ft_special_strcmp(s, env->env[i]) == 0)
		{
			env->env[i] = NULL;
			env->num_env--;
			break ;
		}
	}
}

void	ft_unset(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (i < (*cmd)->num_arg)
	{
		ft_unset_strcmp((*cmd)->arg[i], (*cmd)->env);
		i++;
	}
}