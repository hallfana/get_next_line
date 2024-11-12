/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:10:27 by samberna          #+#    #+#             */
/*   Updated: 2024/11/12 13:27:17 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = (char *)malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (int)len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	get_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return(0);
}

void	*ft_realloc(void *old, size_t oldsz, size_t newsz)
{
	size_t	i;
	char	*new;

	if (newsz == 0)
		return (NULL);
	new = malloc(newsz);
	if (!new)
		return (new);
	i = 0;
	while (i < oldsz)
	{
		((char *)new)[i] = ((char*)old)[i];
		i++;
	}
	free(old);
	return (new);
}

char	*get_next_line(int fd)
{
	static t_gnl	*gnl;
	int				n;
	int				line;
	char			*line_r;

	if (!gnl)
	{
		gnl = (t_gnl*)malloc(sizeof(t_gnl));
		gnl->fd = fd;
		gnl->offset_cursor = 0;
		gnl->buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		gnl->next = NULL;
	}
	if (!gnl->buffer)
		return (NULL);
	else
	{
		n = read(fd, gnl->buffer, BUFFER_SIZE);
		gnl->buffer = ft_realloc(gnl->buffer, BUFFER_SIZE + gnl->offset_cursor, n);
		if (!gnl->buffer)
			return (NULL);
		line = get_line(gnl->buffer);
		while (line == 0 || n != 0)
		{
			gnl->offset_cursor += n;
			gnl->buffer = ft_realloc(gnl->buffer, gnl->offset_cursor, gnl->offset_cursor + BUFFER_SIZE);
			if (!gnl->buffer)
				return (NULL);
			n = read(fd, gnl->buffer + gnl->offset_cursor, BUFFER_SIZE);
			line = get_line(gnl->buffer);
		}
		if (line > 0)
		{
			printf("iner:%d:%s\n", line, gnl->buffer);
			line_r = ft_substr(gnl->buffer, 0, line);
			gnl->buffer = ft_substr(gnl->buffer, line + 1, gnl->offset_cursor - line);
			gnl->buffer = ft_realloc(gnl->buffer, gnl->offset_cursor, gnl->offset_cursor - line);
			gnl->offset_cursor = gnl->offset_cursor - line;
			return (line_r);
		}
		printf("\nFOUND LINE %d\n", line);
	}
	return (NULL);
}

#include <fcntl.h>
int	main(int argc, char **argv)
{
	int 	fd_open;
	char	*data_read;

	if ((fd_open = open("dataset.txt", O_RDONLY)) == -1)
	{
		printf("[!] Error openning the file, please create the file or change the name!");
		return (1);
	}
	data_read = get_next_line(fd_open);
	while (data_read)
	{
		data_read = get_next_line(fd_open);
		printf("readed data: %s\n", data_read);
	}
	return (0);
}
