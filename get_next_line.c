/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seantoni <seantoni@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:54:45 by seantoni          #+#    #+#             */
/*   Updated: 2024/02/19 23:43:06 by seantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*strg_clean(char *str)
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

char	*new_line(char *str)
{
	char	*ptr;
	char	*str_new;
	int		len;

	ptr = ft_strchr(str, '\n');
	len = (ptr - str) + 1;
	str_new = ft_substr(str, 0, len);
	if (!str_new)
		return (NULL);
	return (str_new);
}

char	*leer_descr(int fd, char *str)
{
	int		len;
	char	*str_new;

	str_new = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_new)
		return (ft_free(&str));
	len = 1;
	str_new[0] = '\0';
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

char	*get_next_line(int fd)
{
	char		*line;
	static char	*strg = {0};

	if (fd < 0)
		return (NULL);
	if ((strg && !ft_strchr(strg, '\n')) || !strg)
		strg = leer_descr(fd, strg);
	if (!strg)
		return (NULL);
	line = new_line(strg);
	if (!line)
		return (ft_free(&strg));
	strg = strg_clean(strg);
	return (line);
}
