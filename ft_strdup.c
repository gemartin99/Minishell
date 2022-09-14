#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		ft_free();
	ft_strlcpy (res, s1, ft_strlen(s1) + 1);
	return (res);
}
