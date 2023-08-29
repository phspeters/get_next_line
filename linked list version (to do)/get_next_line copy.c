/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/29 11:30:21 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buff;
	char			*line_read;
	char			*next_line;
	static t_list	*list = NULL;
	int				bytes_read;

	line_read = initialize_and_check_errors(fd, &list, &buff,
			&bytes_read);
	if (line_read == NULL)
		return (NULL);
	if (read_from_file(fd, &line_read, buff, &bytes_read) == NULL)
		return (NULL);
	bytes_read = handle_end_of_file(line_read, &bytes_read);
	if (bytes_read < 0)
		return (NULL);
	next_line = create_next_line(line_read, &list);
	free(line_read);
	return (next_line);
}

char	*initialize_and_check_errors(int fd, char **list,
		char **buff, int *bytes_read)
{
	char	*line_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*bytes_read = BUFFER_SIZE;
	if ((*list) == NULL)
		*list = ft_strdup("");
	line_read = ft_strdup(*list);
	free(*list);
	*list = NULL;
	*buff = ft_calloc(1, BUFFER_SIZE + 1);
	return (line_read);
}

int	*read_from_file(int fd, char **line_read, char *buff,
		int *bytes_read)
{
	char	*temp;

	while (!ft_strchr(*line_read, '\n') && *bytes_read == BUFFER_SIZE)
	{
		*bytes_read = read(fd, buff, BUFFER_SIZE);
		if (*bytes_read < 0)
		{
			free(buff);
			free(*line_read);
			return (NULL);
		}
		buff[*bytes_read] = '\0';
		temp = *line_read;
		*line_read = ft_strjoin(*line_read, buff);
		free(temp);
	}
	free(buff);
	return (bytes_read);
}

int	handle_end_of_file(char *line_read, int *bytes_read)
{
	if (*bytes_read == 0 && *line_read == '\0')
	{
		free(line_read);
		return (-1);
	}
	return (*bytes_read);
}

char	*create_next_line(char *line_read, char **list)
{
	int		i;
	char	*next_line;

	i = 0;
	next_line = ft_calloc(1, ft_strlen(line_read) + 1);
	while (line_read[i] != '\n' && line_read[i] != '\0')
	{
		next_line[i] = line_read[i];
		i++;
	}
	if (line_read[i] == '\n')
		next_line[i++] = '\n';
	if (line_read[i] != '\0')
		*list = ft_strdup(&line_read[i]);
	else
		next_line[i] = '\0';
	return (next_line);
}
