/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:09:36 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/08 17:30:51 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr_gnl(char *str, int c)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
}

char	*ft_strdup_gnl(char *src)
{
	int		i;
	char	*str_dup;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
		i++;
	str_dup = (char *)malloc((i + 1) * sizeof(char));
	if (str_dup == NULL)
		return (NULL);
	i = 0;
	while (str_dup != NULL && src[i] != '\0')
	{
		str_dup[i] = src[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}

void	*ft_memcpy_gnl(void *dest, const char *src, size_t len)
{
	size_t	i;
	char	*destination;
	char	*source;

	i = 0;
	destination = (char *)dest;
	source = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	if (dest != src)
	{
		while (i < len)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len;
	char	*joined;

	if (!s1 && !s2)
		return (ft_strdup_gnl(""));
	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (ft_strdup_gnl(s1));
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	joined = (char *)malloc((len + 1) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	ft_memcpy_gnl(joined, s1, ft_strlen_gnl(s1));
	ft_memcpy_gnl((joined + ft_strlen_gnl(s1)), s2, ft_strlen_gnl(s2));
	joined[len] = '\0';
	free(s1);
	return (joined);
}