/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seantoni <seantoni@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 23:22:47 by seantoni          #+#    #+#             */
/*   Updated: 2024/02/20 21:12:40 by seantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str != c)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return (str);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strcpy(char *dest, char *src)
{
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) + 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (ft_free(&s1));
	ft_strcpy(str, s1);
	ft_strcpy(str + len_s1, s2);
	free(s1);
	return (str);
}

char	*ft_substr(char *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*str_new;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < start)
	{
		str_new = (char *)malloc(sizeof(char) + 1);
		if (!str_new)
			return (NULL);
		str_new[0] = '\0';
		return (str_new);
	}
	if (ft_strlen(str) - start < len)
		len = ft_strlen(str) - start;
	str_new = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_new)
		return (NULL);
	i = 0;
	while (str[start] && i < len && start < ft_strlen(str))
		str_new[i++] = str[start++];
	str_new[i] = '\0';
	return (str_new);
}
