/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:50:24 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/24 11:58:13 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

char		*get_next_line(int fd);
static char	*initialize_and_check_errors(int fd, char **remaining_line,
				char **buff, int *bytes_read);
static int	*read_from_file(int fd, char **line_read, char *buff,
				int *bytes_read);
static int	handle_end_of_file(char *line_read, int *bytes_read);
static char	*create_next_line(char *line_read, char **remaining_line);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strlen(char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);

#endif