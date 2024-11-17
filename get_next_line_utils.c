/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:00:58 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 21:16:30 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_realloc(void *old, size_t oldSz, size_t newSz)
{
	size_t	i;
	char	*new;

	new = malloc(newSz);
	if (!new)
		return (new);
	i = 0;
	while (i < oldSz)
	{
		((char *)new)[i] = ((char *)old)[i];
		++i;
	}
	free(old);
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
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
