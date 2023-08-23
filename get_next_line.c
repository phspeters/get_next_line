/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/23 15:25:04 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*buff;
	char		*dirty_line;
	char		*clean_line;
	static char	*dirt = NULL;
	int			bytes_read;
	int			i;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	i = 0;
	clean_line = NULL;
	bytes_read = BUFFER_SIZE;
	if (!dirt)
		dirt = ft_strdup("");
	dirty_line = ft_strdup(dirt);
	free (dirt);
	dirt = NULL;
	buff = ft_calloc(1, BUFFER_SIZE + 1);
	while (!ft_strchr(dirty_line, '\n') && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			free (dirty_line);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		temp = dirty_line;
		dirty_line = ft_strjoin(dirty_line, buff);
		free (temp);
	}
	free (buff);
	if (bytes_read == 0 && *dirty_line == '\0')
	{
		free(dirty_line);
		return (NULL);
	}
	clean_line = ft_calloc(1, ft_strlen(dirty_line) + 1);
	while (dirty_line[i] != '\n' && dirty_line[i] != '\0')
	{
		clean_line[i] = dirty_line[i];
		i++;
	}
	if (dirty_line[i] == '\n')
		clean_line[i++] = '\n';
	if (dirty_line[i] != '\0')
		dirt = ft_strdup(&dirty_line[i]);
	else
		clean_line[i] = '\0';
	free (dirty_line);
	return (clean_line);
}
