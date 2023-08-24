/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:59:49 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/23 20:43:16 by peters           ###   ########.fr       */
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

char	*get_next_line(int fd);
char	*create_clean_line(char *dirty_line, char **dirt);
char	*handle_end_of_file(char *dirty_line, int *bytes_read);
int		*read_from_file(int fd, char **dirty_line, char *buff, int *bytes_read);
char	*initialize_and_check_errors(int fd, char **dirt, char **dirty_line,
			int *bytes_read);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strlen(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

#endif