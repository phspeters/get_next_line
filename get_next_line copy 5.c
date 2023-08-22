/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by peters            #+#    #+#             */
/*   Updated: 2023/08/22 12:28:08 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE];
	char		*dirty_line;
	char		*clean_line;
	static char	*dirt;
	int			bytes_read;
	int			i;
	char 		*temp;

	i = 0;
	if (dirt)
		dirty_line = ft_strdup(dirt);
	else
		dirty_line = ft_calloc(1, 1);
	while (!ft_strchr(dirty_line, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		else
		{
			buff[bytes_read] = '\0';
			temp = dirty_line;
			dirty_line = ft_strjoin(dirty_line, buff);
			free(temp);
		}
	}
	if (bytes_read == 0 && !dirt)
	{
		free(dirty_line);
		return (NULL);
	}
	clean_line = ft_calloc(1, ft_strlen(dirty_line));
	while (dirty_line[i] != '\n' && dirty_line[i] != '\0')
	{
		clean_line[i] = dirty_line[i];
		i++;
	}
	if (dirty_line[i] == '\n')
		clean_line[i++] = '\n';
	if (dirty_line[i] != '\0')
	{
		dirt = ft_strdup(&dirty_line[i]);
	}
	else
	{
		clean_line[i] = '\0';
		dirt = NULL;
	}
	free(dirty_line);
	return (clean_line);
}
