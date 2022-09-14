#include "minishell.h"

char	*ft_strtrim(char *s1, char set)
{
	size_t	len;

	if (!s1 || !set)
		return (0);
	while (*s1 && *s1 != set)
		s1++;
	len = ft_strlen(s1);
	while (s1[len] != set && len)
		len--;
	return (ft_substr(s1, 0, len + 1));
}
