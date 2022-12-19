/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:23:26 by smiro             #+#    #+#             */
/*   Updated: 2022/10/29 18:27:53 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*nextline(char *staticbuf, char *line)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (staticbuf[i] && staticbuf[i] != '\n')
		i++;
	if (!staticbuf[i] || !line)
	{
		free(staticbuf);
		return (NULL);
	}
	temp = ft_calloc(ft_strlen(staticbuf) - i, sizeof(char));
	if (!temp)
	{
		free(staticbuf);
		return (NULL);
	}
	i++;
	j = 0;
	while (staticbuf[i])
		temp[j++] = staticbuf[i++];
	free(staticbuf);
	return (temp);
}

static char	*findline(char *staticbuf)
{
	char	*line;
	int		i;

	i = 0;
	if (!staticbuf[i])
		return (NULL);
	while (staticbuf[i] && staticbuf[i] != '\n')
		i++;
	if (staticbuf[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (staticbuf[i] && staticbuf[i] != '\n')
	{
		line[i] = staticbuf[i];
		i++;
	}
	if (staticbuf[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ftjoinbufs(char *buf, char *staticbuf)
{
	char	*temp;

	temp = ft_strjoin(staticbuf, buf);
	if (!temp)
	{
		free(staticbuf);
		return (NULL);
	}
	free(staticbuf);
	return (temp);
}

static char	*ftread(int fd, char *staticbuf)
{
	char		*buf;
	ssize_t		bytesread;

	if (!staticbuf)
		staticbuf = ft_calloc(1, 1);
	if (!staticbuf)
		return (NULL);
	bytesread = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (ftfree(staticbuf));
	while (bytesread > 0)
	{
		bytesread = read(fd, buf, BUFFER_SIZE);
		if (bytesread == -1)
			return (ftfree(buf));
		buf[bytesread] = 0;
		staticbuf = ftjoinbufs(buf, staticbuf);
		if (ft_strchr(buf, '\n') || !staticbuf)
			break ;
	}
	free(buf);
	return (staticbuf);
}

char	*get_next_line(int fd)
{
	static char	*staticbuf[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		if (staticbuf[fd])
		{
			free(staticbuf[fd]);
			staticbuf[fd] = NULL;
		}
		return (NULL);
	}
	staticbuf[fd] = ftread(fd, staticbuf[fd]);
	if (!staticbuf[fd])
		return (NULL);
	line = findline(staticbuf[fd]);
	staticbuf[fd] = nextline(staticbuf[fd], line);
	return (line);
}
