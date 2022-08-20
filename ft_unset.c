#include "minishell.h"

int	ft_special_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	//printf("antes s1 %s\n s2 %s\n", s1, s2);
	if (!s2)
		return (-1);
	while (s2[i] && s2[i + 1] && s2[i + 1] != '=' && s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	//printf("despuesd s1 %s\n s2 %s\n", s1, s2);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int ft_unset_strcmp(char *s, t_list *d)
{
	int i;

	i = -1;
	//hacer funcion que detecte si en algun argumento hay caracteres
	//especiales y si los hay printar el siguiente error "bash: unset: `%s': not a valid identifier"
	if (!s[0] || s[0] == '=' || s[0] == '?' || s[0] == '!')
	{
		printf("bash: unset: `%s': not a valid identifier\n", s);
		return (0);
	}
	while (++i < d->num_env)
	{
		//printf("1 %s\n 2 %s\n", s, d->ent_var[i]);
		if (ft_special_strcmp(s, d->ent_var[i]) == 0)
		{
			d->ent_var[i] = NULL;
			break ;
		}
	}
	return (0);
}

int 	ft_unset(t_list *d)
{
	int i;

	i = 1;
	while (i < d->num_args)
	{
		if (ft_unset_strcmp(d->argu[i], d) == 0)
			;
		i++;
	}
	return (0);
}
