/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:39:35 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 16:21:28 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // Add this for debug prints

t_gnl	*get_gnl(t_gnl *lst, int fd)
{
	t_gnl	*head;
	t_gnl	*new;

	head = lst;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
	}
	new = (t_gnl *)malloc(sizeof(t_gnl));
	new->fd = fd;
	new->buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	new->offset = 0;
	new->next = NULL;
	if (head)
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new;
		return (head->next);
	}
	else
		return (new);
}

t_gnl	*extract(t_gnl	*lst)
{
	int		i;
	char	*line;
	char	*tmp_buf;
	int		tmp_offset;

	i = 0;
	while(lst->buf[i] != '\n' && i < lst->offset)
		i++;
	//printf("off=%d\n", lst->offset);
	line = ft_substr(lst->buf, 0, i + 1);
	//printf("line=%s\n", line);
	//printf("i=%d,+1=%c,+2=%c\n", i, lst->buf[i + 1], lst->buf[i + 2]);
	tmp_buf = ft_substr(lst->buf, i + 1, lst->offset - i);
	//printf("10\n");
	tmp_offset = lst->offset - i;
	//printf("tmp_buf=%s,tmp_offset=%d\n", tmp_buf, tmp_offset);
	lst->buf = tmp_buf;
	lst->offset = tmp_offset;
	lst->line = line;
	return (lst);
}

char	*get_next_line(int fd)
{
	//static t_gnl	*datastore;
	static t_gnl			*lst;
	int				n;

	if (!lst)
	{
		lst = (t_gnl *)malloc(sizeof(t_gnl));
		lst->fd = fd;
		lst->buf = NULL;
		lst->offset = 0;
		lst->next = NULL;
		lst->line = NULL;
	}
	
	//lst = get_gnl(datastore, fd);

	/*if (!lst || fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!lst->buf)
		lst->buf = malloc(BUFFER_SIZE);
	printf("BUFFER ONE: %s, offset %d\n", lst->buf, lst->offset);
	n = read(lst->fd, lst->buf + lst->offset, BUFFER_SIZE);
	printf("BUFFER TWO: %s, offset %d\n", lst->buf, lst->offset);
	while (n > 0)
	{
		lst->offset += n;
		printf("buf=%s,off=%d\n", lst->buf, lst->offset);
		lst->buf = ft_realloc(lst->buf, lst->offset, lst->offset + BUFFER_SIZE);
		if (ft_strnchr(lst->buf, '\n', lst->offset) != NULL)
			lst = extract(lst);
		if (lst->line)
		{
			printf("LINE=%s,OFFSET=%d,BUF=%s\n", lst->line, lst->offset, lst->buf);
			return (lst->line);
		}
		if (!lst->buf)
			return (NULL);
		n = read(fd, lst->buf + lst->offset, BUFFER_SIZE);
	}
    return (NULL);*/

	if (!lst || fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!lst->buf)
		lst->buf = malloc(BUFFER_SIZE);
	while (1)
	{
		if (lst->buf)
			lst->buf = ft_realloc(lst->buf, lst->offset, lst->offset + BUFFER_SIZE);
		n = read(lst->fd, lst->buf + lst->offset, BUFFER_SIZE);
		lst->offset += n;
		lst = extract(lst);
		if (lst->line != NULL)
			return (lst->line);
	}
    return (NULL);
}

int main()
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
        printf("FOUND: %s\n\n\n\n", line);
        free(line);
    }
    close(fd);
    return (0);
}

