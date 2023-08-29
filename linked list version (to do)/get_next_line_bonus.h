/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:50:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/29 11:25:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;
char	*get_next_line(int fd);
char	*initialize_and_check_errors(int fd, char **remaining_line, char **buff,
			int *bytes_read);
int		*read_from_file(int fd, char **line_read, char *buff, int *bytes_read);
int		handle_end_of_file(char *line_read, int *bytes_read);
char	*create_next_line(char *line_read, char **remaining_line);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

#endif