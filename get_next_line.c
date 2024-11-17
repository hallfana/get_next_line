/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:39:35 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 11:15:27 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	*lst;
	t_gnl			*tmp;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		tmp = (t_gnl *)malloc(sizeof(t_gnl));
		if (!tmp)
			return (NULL);
		tmp->buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!tmp->buffer)
			return (NULL);
		tmp->str = NULL;
		tmp->fd = fd;
		tmp->offset = 0;
		tmp->ret = 0;
		tmp->next = lst;
		lst = tmp;
	}
	line = ft_strjoin(tmp->str, "");
	while (!ft_strchr(line, '\n') && (tmp->ret = read(fd, tmp->buffer, BUFFER_SIZE)) > 0)
	{
		tmp->buffer[tmp->ret] = '\0';
		tmp->str = ft_strjoin(tmp->str, tmp->buffer);
		line = ft_strjoin(tmp->str, "");
	}
	if (tmp->ret == 0)
	{
		free(tmp->buffer);
		free(tmp->str);
		free(tmp);
	}
	return (line);
}

#include <stdio.h>
int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}