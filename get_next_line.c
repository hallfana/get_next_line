/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:39:35 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 21:16:57 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_getline(char *buf, int sz)
{
	int	i;

	i = 0;
	while (buf[i] && i < sz)
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_read(char **buf, int *sz, int fd)
{
	int	n;

	*buf = ft_realloc(*buf, *sz, *sz + BUFFER_SIZE);
	if (!*buf)
		return (-1);
	n = read(fd, *buf + *sz, BUFFER_SIZE);
	if (n > 0)
		*sz += n;
	return (n);
}

char	*ft_extract_line(char **buf, int *sz)
{
	int		i;
	char	*line;

	i = ft_getline(*buf, *sz);
	if (i == -1)
		return (NULL);
	line = ft_substr(*buf, 0, i);
	*buf = ft_substr(*buf, i + 1, *sz - i - 1);
	*sz -= i + 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	sz;
	int			n;
	char		*line;

	if (fd == 0)
		return (NULL);
	n = 1;
	while (n > 0)
	{
		n = ft_read(&buf, &sz, fd);
		if (n == -1)
			return (NULL);
		line = ft_extract_line(&buf, &sz);
		if (line)
			return (line);
	}
	if (n == 0 && sz > 0)
	{
		line = ft_substr(buf, 0, sz);
		buf = NULL;
		sz = 0;
		return (line);
	}
	return (NULL);
}

/*int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("FOUND: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
