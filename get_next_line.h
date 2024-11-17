/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:40:35 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 16:48:13 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_gnl
{
	char			*buf;
	int				offset;
	int				fd;
	char			*line;
	struct s_gnl	*next;
} t_gnl;

char	*get_next_line(int fd);
int		ft_strnchr(const char *s, int c, int sw);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, int start, int len);
int		ft_strlen(const char *s);
void	*ft_realloc(void *old, size_t oldSz, size_t newSz);

#endif