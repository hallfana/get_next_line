/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:39:35 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 18:34:50 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_getline(char *buf, int sz)
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

char	*get_next_line(int fd)
{
	static char	*buf;
	static int			sz;
	static int			n;
	static int			m;
	char				*tmp;

	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	sz = 0;
	n = read(fd, buf + sz, BUFFER_SIZE);
	while (n > 0)
	{
		printf("|n last:%d|\n", n);
		sz += n;
		buf = ft_realloc(buf, sz, sz + BUFFER_SIZE);
		if (!buf)
			return (NULL);
		if (ft_getline(buf, sz) > 0)
		{
			printf("|HEY: %s|\n", ft_substr(buf, 0, ft_getline(buf, sz) + 1));
			printf("|JA: %s|\n", ft_substr(buf, ft_getline(buf, sz) + 1, sz - ft_getline(buf, sz) - 1));
			//tmp = ft_substr(buf, 0, ft_getline(buf, sz) + 1);
			m = sz - (ft_getline(buf, sz) + 1);
			buf = ft_substr(buf, ft_getline(buf, sz) + 1, sz - ft_getline(buf, sz) - 1);
			printf("|yes: %s|\n", buf);
			printf("|inner-m last:%d|\n", m);	
			sz = m;
			//return (tmp);
		}
		n = read(fd, buf + sz, BUFFER_SIZE);
	}
	if (n == 0 && buf)
		printf("|HEY: %s|\n", ft_substr(buf, 0, sz));
		//return (ft_substr(buf, 0, sz));
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
        printf("|FOUND: %s|", line);
        free(line);
    }
    close(fd);
    return (0);
}

