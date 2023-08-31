/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/31 20:26:46 by pehenri2         ###   ########.fr       */
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
	char			*rest;
	int				i;
	int				line_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	//botar content como NULL?
	if (!head)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			return NULL;
		}
		buff[bytes_read] = '\0';
		new = ft_lstnew(buff);
		ft_lstadd_back(&head, new);
	}
	current = head;
	//verificar buffer?
	// iniciar como NULL e colocar condição para entrar se NULL e depois sar strchr no buff
	while (!ft_strchr(current->content, '\n') && bytes_read == BUFFER_SIZE)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			ft_lstclear(&head, free);
			return NULL;
		}
		buff[bytes_read] = '\0';
		new = ft_lstnew(buff);
		ft_lstadd_back(&head, new);
		current = current->next;
	}
	if (bytes_read == 0 && head->content[0] == '\0')
	{
		ft_lstclear(&head, free);
		return (NULL);
	}
	current = head;
	i = 0;
	line_len = 0;
	while(current->content[i] != '\n')
	{
		if (current->content[i] == '\0')
		{
			current = current->next;
			i = 0;
		}
		else
		{
			line_len++;
			i++;
		}
		if(current->content[i] == '\n')
			line_len++;
	}
	next_line = malloc(sizeof(char) * (line_len + 1));
	current = head;
	line_len = 0;
	while(current)
	{
		i = 0;
		while(i < BUFFER_SIZE)
		{
			if (current->content[i] != '\n' && current->content[i] != '\0')
			{
				next_line[line_len] = current->content[i];
				i++;
				line_len++;
			}
			else
			{
				if (current->content[i] == '\n')
					next_line[line_len++] = '\n';
				next_line[line_len] = '\0';
				rest = ft_strdup(current->content + i);
				new = ft_lstnew(rest);
				break ;
			}
		}
		current = current->next;
	}
	ft_lstclear(&head, free);
	head = new;
	return (next_line);
}
