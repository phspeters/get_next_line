/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by peters            #+#    #+#             */
/*   Updated: 2023/08/20 12:50:55 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*dirty_line;
	char		*clean_line;
	static char	*dirt = NULL;
	int			bytes_read;
	int			i;
	int			j;

	i = 0;
	if (dirt)
		dirty_line = ft_strdup(dirt);
	else
		dirty_line = ft_calloc(1, 1);
	while (!ft_strchr(dirty_line, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buff[bytes_read] = '\0';
		dirt = dirty_line;
		dirty_line = ft_strjoin(dirty_line, buff);
		free(dirt);
	}
	if (bytes_read == 0 && !ft_strchr(dirty_line, '\n'))
	{
		free(dirty_line);
		return (NULL);
	}
	clean_line = ft_calloc(1, ft_strlen(dirty_line));
	while (dirty_line[i] != '\n' && dirty_line[i] != '\0')
	{
		clean_line[i] = dirty_line[i];
		i++;
	}
	if (dirty_line[i] == '\n')
		clean_line[i++] = '\n';
	dirt = ft_calloc(1, ft_strlen(dirty_line) - i + 1);
	j = 0;
	while (dirty_line[i + j] != '\0')
	{
		dirt[j] = dirty_line[i + j];
		j++;
	}
	free(dirty_line);
	return (clean_line);
}

/////////////////////////////////////////////////////////

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		s_size;

	s_size = ft_strlen((char *)s) + 1;
	dup = malloc(sizeof(char) * s_size);
	if (dup == NULL)
		return (NULL);
	dup = ft_memcpy(dup, s, s_size);
	return (dup);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total_size = (nmemb * size);
	if (total_size / nmemb != size)
		return (NULL);
	alloc = malloc(total_size);
	if (alloc != NULL)
		ft_bzero(alloc, total_size);
	return (alloc);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = '\0';
		p++;
		n--;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
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

int	main(void)
{
	int	fd;
	int	i;

	i = 0;
	fd = open("teste.txt", O_RDONLY);
	while (i < 15)
	{
		printf("gnl %i: %s", i, get_next_line(fd));
		i++;
	}
}
