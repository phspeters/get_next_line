/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:50:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/09/03 20:40:58 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;
char	*get_next_line(int fd);
int		initialize_and_check_errors(int fd, t_list **head, int *bytes_read);
int		*read_from_fd_into_list(int fd, t_list **head, int *bytes_read);
char	*create_line_from_list(t_list **head, int length);
char	*create_rest(t_list **head);
char	*create_new_list_with_rest(t_list **head, char *rest);
int		is_end_of_file(int bytes_read, t_list **head);
void	*handle_alloc_error(t_list **head, char *str);
int		get_line_length(t_list *head);
// libft
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);

#endif