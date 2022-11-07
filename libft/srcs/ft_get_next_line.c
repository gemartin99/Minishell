/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpou-ale <tpou-ale@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:45:56 by tpou-ale          #+#    #+#             */
/*   Updated: 2022/01/25 17:46:01 by tpou-ale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_line(char **map)
{
	char	*line;
	char	*buff;

	if (!*map || !**map)
		return (NULL);
	if (!ft_strchr(*map, '\n'))
	{
		line = ft_strdup(*map);
		free(*map);
		*map = NULL;
		return (line);
	}
	line = ft_substr(*map, 0, ft_strchr(*map, '\n') - *map + 1);
	if (!line)
		return (line);
	buff = ft_substr(*map, ft_strchr(*map, '\n') - *map + 1, ft_strlen(*map));
	if (!ft_strlen(buff))
	{
		free(buff);
		buff = NULL;
	}
	free(*map);
	*map = buff;
	return (line);
}

char	*ft_get_next_line(int fd)
{
	static char	*map[MAX_FD + 1];
	char		*line;
	char		*buff;
	ssize_t		size;

	if (BUFFER_SIZE < 0 || fd < 0 || fd > MAX_FD)
		return (NULL);
	buff = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	while (size > 0)
	{
		buff[size] = '\0';
		line = ft_strjoin(map[fd], buff);
		if (map[fd])
			free(map[fd]);
		map[fd] = line;
		if (ft_strchr(map[fd], '\n'))
			break ;
		size = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (ft_get_line(&map[fd]));
}
