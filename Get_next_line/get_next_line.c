/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:01:11 by jbaringo          #+#    #+#             */
/*   Updated: 2019/12/13 13:35:00 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		next_line(char **text, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*text)[i] != '\n' && (*text)[i] != '\0')
		i++;
	if ((*text)[i] == '\n')
	{
		*line = ft_substr(*text, 0, i);
		tmp = ft_strdup(&((*text)[i + 1]));
		free(*text);
		*text = tmp;
	}
	else
	{
		*line = ft_substr(*text, 0, i);
		free(*text);
		*text = NULL;
		return (0);
	}
	return (1);
}

int		check(int fd, int t_read, char **text, char **line)
{
	if (t_read < 0)
		return (-1);
	else if ((t_read == 0 && text[fd] == NULL) || text[fd][0] == '\0')
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (next_line((&text[fd]), line));
}

int		get_next_line(int fd, char **line)
{
	int				t_read;
	char			buff[BUFFER_SIZE + 1];
	static char		*text[4096];
	char			*tmp;

	if (fd < 0 || !line || !BUFFER_SIZE)
		return (-1);
	while ((t_read = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[t_read] = '\0';
		if (text[fd] == NULL)
			text[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(text[fd], buff);
			free(text[fd]);
			text[fd] = tmp;
		}
		if (ft_strchr(text[fd], '\n'))
			break ;
	}
	return (check(fd, t_read, text, line));
}
