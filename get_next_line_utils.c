/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:00:58 by samberna          #+#    #+#             */
/*   Updated: 2024/11/17 16:58:43 by samberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, int start, int len)
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

int	ft_strnchr(const char *s, int c, int sw)
{
	size_t	i;

	i = 0;
	if (c == 0)
		return (-1);
	while (s[i], i < sw)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	str[i] = 0;
	return (str);
}

int ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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