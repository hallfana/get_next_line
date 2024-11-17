/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:39:35 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 17:15:57 by samberna         ###   ########.fr       */
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

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[j])
		j++;
	while (s2[i])
	{
		s1[j] = s2[i];
		i++;
		j++;
	}
	s1[j] = '\0';
	return (s1);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (n == 0)
		return ;
	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

char	*ft_read(int fd, char *buf, int sw)
{
	char	*tmp_buf;
	int		n;

	tmp_buf = (char *)malloc(sizeof(char) * sw);
	n = read(fd, tmp_buf, sw);
	buf = ft_realloc(buf, ft_strlen(buf), ft_strlen(buf) + n + 1);
	buf = ft_strcat(buf, tmp_buf);
	buf[ft_strlen(buf)] = '\0';
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;

	if (!buf)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		ft_bzero(buf, BUFFER_SIZE + 1);
		buf[BUFFER_SIZE] = '\0';
	}
	buf = ft_read(fd, buf, BUFFER_SIZE);
	return (buf);
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

