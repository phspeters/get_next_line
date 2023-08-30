/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/30 19:41:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*head;
	char			*buff;
	int				bytes_read;
	t_list			*current;
	t_list			*new;
	t_list			*temp;
	char			*content;
	int				i;
	int				j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	current = head;
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			return NULL;
		}
		buff[bytes_read] = '\0';
		new = ft_lstnew(ft_strdup(buff));
		ft_lstadd_back(&head, new);
		if (ft_strchr(current->content, '\n'))
			break ;
		else
			current = current->next;
	}
	free (buff);
	current = head;
	i = 0;
	j = 0;
	while(current->content[i] != '\n')
	{
		if (current->content[i] == '\0')
		{
			current = current->next;
			i = 0;
		}
		else
		{
			j++;
			i++;
		}
	}
	next_line = malloc(sizeof(char) * (j + 2));
	current = head;
	while(current)
	{
		i = 0;
		while(i < BUFFER_SIZE)
		{
			if (current->content[i] != '\n' && current->content[i] != '\0')
			{
				next_line[i] = current->content[i];
				i++;
			}
			else
			{
				if (current->content[i] == '\n')
					next_line[i++] = '\n';
				next_line[i] = '\0';
				content = ft_strdup(current->content + i);
				current = ft_lstnew(content);
				free (content);
				break ;
			}
		}
		current = current->next;
	}
	ft_lstclear(&head, free);
	head = current;
	return (next_line);
}
