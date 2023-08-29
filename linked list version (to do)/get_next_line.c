/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/29 16:54:17 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*list;
	char			*buff;
	int				bytes_read;
	t_list			*current;
	t_list			*cursor;
	int				i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	if (!list)
		list = ft_lstnew("");
	current = list;
	while (ft_strchr(current->content, '\n') && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			return NULL;
		}
		buff[bytes_read] = '\0';
		current = ft_lstnew(buff);
		ft_lstadd_back(&list, current);
		current = current->next;
	}
	free (buff);
	while(cursor)
	{
		i = 0;
		while(i < BUFFER_SIZE)
		{
			if (cursor->content[i] != '\n')
			{
				next_line[i] = cursor->content[i];
				i++;
			}
			else
			{
				next_line[i++] = '\n';
				next_line[i] = '\0';
				content = ft_strdup(cursor->content + i);
				new = ft_lstnew(content);
			}
		}
		current = current->next;
	}
	return (next_line);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((s[i] == (unsigned char)c))
		return ((char *)s + i);
	return (NULL);
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int	i;

	while ((line = get_next_line(0)))
	{
		line = get_next_line(0);
		printf("Line [%i] %s\n", i, line);
		i++;
	}
}