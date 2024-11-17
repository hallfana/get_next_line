/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:39:35 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 22:45:44 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_getline(char *buf, int sz)
{
	int	i;

	if (!buf)
		return (-1);
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
	int		n;
	char	*temp;

	temp = ft_realloc(*buf, *sz, *sz + BUFFER_SIZE);
	if (!temp)
	{
		free(*buf);
		*buf = NULL;
		*sz = 0;
		return (-1);
	}
	*buf = temp;
	n = read(fd, *buf + *sz, BUFFER_SIZE);
	if (n < 0)
	{
		free(*buf);
		*buf = NULL;
		*sz = 0;
		return (-1);
	}
	if (n > 0)
		*sz += n;
	(*buf)[*sz] = '\0';
	return (n);
}

int	ft_extract_line(char **buf, int *sz, char **l)
{
	int		i;
	char	*line;
	char	*temp;

	i = ft_getline(*buf, *sz);
	if (i == -1)
		return (0);
	line = ft_substr(*buf, 0, i + 1);
	temp = ft_substr(*buf, i + 1, *sz - i - 1);
	free(*buf);
	*buf = temp;
	*sz -= i + 1;
	*l = line;
	return (1);
}

char	*free_n_return(char **buf)
{
	free(*buf);
	*buf = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	sz;
	int			n;
	char		*line;

	if (fd < 0)
		return (free_n_return(&buf));
	if (ft_extract_line(&buf, &sz, &line) == 1)
		return (line);
	while (1)
	{
		n = ft_read(&buf, &sz, fd);
		if (n == -1 || (n == 0 && sz == 0))
			return (free_n_return(&buf));
		if (n == 0 && sz > 0)
		{
			line = ft_substr(buf, 0, sz);
			sz = 0;
			(void)free_n_return(&buf);
			return (line);
		}
		if (ft_extract_line(&buf, &sz, &line) == 1)
			return (line);
	}
}

/*int main()
{
	int fd = 0;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("FOUND:%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
