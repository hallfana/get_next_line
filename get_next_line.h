/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:08:53 by samberna          #+#    #+#             */
/*   Updated: 2024/11/12 13:08:15 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 512
# endif

typedef struct s_gnl
{
	int				fd;
	int				offset_cursor;
	char			*buffer;
	struct s_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);

#endif