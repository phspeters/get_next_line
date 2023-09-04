/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:27 by pehenri2          #+#    #+#             */
/*   Updated: 2023/09/03 20:47:41 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_end_of_file(int bytes_read, t_list **head)
{
	if (bytes_read == 0 && (*head)->content[0] == '\0')
	{
		ft_lstclear(head, free);
		return (1);
	}
	return (0);
}

void	*handle_alloc_error(t_list **head, char *str)
{
	if (str)
		free (str);
	ft_lstclear(head, free);
	return (NULL);
}

int	get_line_length(t_list *head)
{
	t_list	*current;
	int		content_len;
	int		line_len;

	current = head;
	content_len = 0;
	line_len = 0;
	while (current != NULL && current->content[content_len] != '\n')
	{
		if (current->content[content_len] != '\0')
		{
			line_len++;
			content_len++;
		}
		else
		{
			current = current->next;
			content_len = 0;
		}
	}
	if (current != NULL && current->content[content_len] == '\n')
		line_len++;
	return (line_len);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_element;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last_element = ft_lstlast(*lst);
		last_element->next = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current;
		del(current->content);
		current = current->next;
		free(temp);
	}
	*lst = NULL;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	del(lst->content);
	free(lst);
	return ;
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

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		s_size;
	int		i;

	s_size = ft_strlen((char *)s) + 1;
	dup = malloc(sizeof(char) * s_size);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < s_size)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
