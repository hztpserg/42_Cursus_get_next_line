/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seantoni <seantoni@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:52:57 by seantoni          #+#    #+#             */
/*   Updated: 2024/02/23 03:13:06 by seantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*leer_descr(int fd, char *str)
{
	char	*str_new;
	int		len;

	str_new = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_new)
		return (ft_free(&str));
	str_new[0] = '\0';
	len = 1;
	while (len > 0 && !ft_strchr(str_new, '\n'))
	{
		len = read(fd, str_new, BUFFER_SIZE);
		if (len > 0)
		{
			str_new[len] = '\0';
			str = ft_strjoin(str, str_new);
		}
	}
	free(str_new);
	if (len == -1)
		return (ft_free(&str));
	return (str);
}

char	*put_line(char *str)
{
	char	*str_new;
	char	*ptr;
	size_t	len;

	ptr = ft_strchr(str, '\n');
	len = (ptr - str) + 1;
	str_new = ft_substr(str, 0, len);
	if (!str_new)
		return (NULL);
	return (str_new);
}

char	*clear_descr(char *str)
{
	char	*str_new;
	char	*ptr;
	size_t	len;

	ptr = ft_strchr(str, '\n');
	if (!ptr)
		return (ft_free(&str));
	len = (ptr - str) + 1;
	if (!str[len])
		return (ft_free(&str));
	str_new = ft_substr(str, len, ft_strlen(str) - len);
	ft_free(&str);
	if (!str_new)
		return (NULL);
	return (str_new);
}

char	*get_next_line(int fd)
{
	char static	*strg[OPEN_MAX];
	char		*line;

	if (fd < 0)
		return (NULL);
	if (!strg[fd] || (strg[fd] && !ft_strchr(strg[fd], '\n')))
		strg[fd] = leer_descr(fd, strg[fd]);
	if (!strg[fd])
		return (NULL);
	line = put_line(strg[fd]);
	if (!line)
		return (ft_free(&strg[fd]));
	strg[fd] = clear_descr(strg[fd]);
	return (line);
}
