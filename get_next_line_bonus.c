/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/23 21:27:19 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*buff;
	char		*dirty_line;
	char		*clean_line;
	static char	*dirt[1024];
	int			bytes_read;

	dirty_line = initialize_and_check_errors(fd, &dirt[fd], &buff, &bytes_read);
	if (dirty_line == NULL)
		return (NULL);
	if (read_from_file(fd, &dirty_line, buff, &bytes_read) == NULL)
		return (NULL);
	bytes_read = handle_end_of_file(dirty_line, &bytes_read);
	if (bytes_read < 0)
		return (NULL);
	clean_line = create_clean_line(dirty_line, &dirt[fd]);
	free(dirty_line);
	return (clean_line);
}

char	*initialize_and_check_errors(int fd, char **dirt, char **buff,
		int *bytes_read)
{
	char	*dirty_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*bytes_read = BUFFER_SIZE;
	if (!(*dirt))
		*dirt = ft_strdup("");
	dirty_line = ft_strdup(*dirt);
	free(*dirt);
	*dirt = NULL;
	*buff = ft_calloc(1, BUFFER_SIZE + 1);
	return (dirty_line);
}

int	*read_from_file(int fd, char **dirty_line, char *buff, int *bytes_read)
{
	char	*temp;

	while (!ft_strchr(*dirty_line, '\n') && *bytes_read == BUFFER_SIZE)
	{
		*bytes_read = read(fd, buff, BUFFER_SIZE);
		if (*bytes_read < 0)
		{
			free(buff);
			free(*dirty_line);
			return (NULL);
		}
		buff[*bytes_read] = '\0';
		temp = *dirty_line;
		*dirty_line = ft_strjoin(*dirty_line, buff);
		free(temp);
	}
	free(buff);
	return (bytes_read);
}

int	handle_end_of_file(char *dirty_line, int *bytes_read)
{
	if (*bytes_read == 0 && *dirty_line == '\0')
	{
		free(dirty_line);
		return (-1);
	}
	return (*bytes_read);
}

char	*create_clean_line(char *dirty_line, char **dirt)
{
	int		i;
	char	*clean_line;

	i = 0;
	clean_line = ft_calloc(1, ft_strlen(dirty_line) + 1);
	while (dirty_line[i] != '\n' && dirty_line[i] != '\0')
	{
		clean_line[i] = dirty_line[i];
		i++;
	}
	if (dirty_line[i] == '\n')
		clean_line[i++] = '\n';
	if (dirty_line[i] != '\0')
		*dirt = ft_strdup(&dirty_line[i]);
	else
		clean_line[i] = '\0';
	return (clean_line);
}
