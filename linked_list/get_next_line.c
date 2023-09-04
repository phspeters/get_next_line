/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/09/03 20:28:50 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	initialize_and_check_errors(int fd, t_list **head, int *bytes_read)
{
	char	*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (*head == NULL)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return (0);
		*bytes_read = read(fd, buff, BUFFER_SIZE);
		if (*bytes_read < 0)
		{
			free(buff);
			return (0);
		}
		buff[*bytes_read] = '\0';
		*head = ft_lstnew(buff);
	}
	return (1);
}

int	*read_from_fd_into_list(int fd, t_list **head, int *bytes_read)
{
	t_list	*current;
	t_list	*new_node;
	char	*buff;

	current = *head;
	*bytes_read = BUFFER_SIZE;
	while (!ft_strchr(current->content, '\n') && *bytes_read == BUFFER_SIZE)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return (handle_alloc_error(head, buff));
		*bytes_read = read(fd, buff, BUFFER_SIZE);
		if (*bytes_read < 0)
			return (handle_alloc_error(head, buff));
		buff[*bytes_read] = '\0';
		new_node = ft_lstnew(buff);
		if (new_node == NULL)
			return (handle_alloc_error(head, buff));
		ft_lstadd_back(head, new_node);
		current = current->next;
	}
	return (bytes_read);
}

char	*create_line_and_rest_from_list(t_list **head, int length, char **rest)
{
	t_list	*current;
	char	*next_line;
	int		line_len;
	int		content_len;

	current = *head;
	content_len = 0;
	line_len = 0;
	next_line = malloc(sizeof(char) * (length + 1));
	if (next_line == NULL)
		return (handle_alloc_error(head, next_line));
	while (current != NULL && current->content[content_len] != '\n')
	{
		if (current->content[content_len] != '\0')
			next_line[line_len++] = current->content[content_len++];
		else
		{
			current = current->next;
			content_len = 0;
		}
	}
	if (current != NULL && current->content[content_len] == '\n')
	{
		next_line[line_len++] = '\n';
		content_len++;
		*rest = ft_strdup(&current->content[content_len]);
		if (*rest == NULL)
			return (handle_alloc_error(head, next_line));
	}
	else
		*rest = ft_strdup("");
	next_line[line_len] = '\0';
	return (next_line);
}

char	*create_new_list_with_rest(t_list **head, char *rest)
{
	t_list			*new_node;

	new_node = ft_lstnew(rest);
	if (new_node == NULL)
	{
		free (rest);
		ft_lstclear(head, free);
		return (NULL);
	}
	ft_lstclear(head, free);
	*head = NULL;
	if (new_node->content[0] != '\0')
		*head = new_node;
	else
		ft_lstdelone(new_node, free);
	return (rest);
}

char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*head;
	int				bytes_read;
	char			*rest;
	int				line_len;

	if (!initialize_and_check_errors(fd, &head, &bytes_read))
		return (NULL);
	if (!read_from_fd_into_list(fd, &head, &bytes_read))
		return (NULL);
	if (is_end_of_file(bytes_read, &head))
		return (NULL);
	line_len = get_line_length(head);
	next_line = create_line_and_rest_from_list(&head, line_len, &rest);
	if (create_new_list_with_rest(&head, rest) == NULL)
		return (NULL);
	return (next_line);
}
