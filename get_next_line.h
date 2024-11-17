/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:40:35 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 22:26:29 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
int		ft_getline(char *buf, int sz);
int		ft_read(char **buf, int *sz, int fd);
int		ft_extract_line(char **buf, int *sz, char **l);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_realloc(void *old, size_t oldSz, size_t newSz);
char	*free_n_return(char **buf);

#endif